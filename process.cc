#include "process.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "build/target/include/magic.h"

int logging = 0;
const char *last_error_message = NULL;

const char *last_error() {
    static const char *result = last_error_message;
    last_error_message = NULL;
    return result;
}

static const char *mime_types[] = {
    "application/gzip",
    "application/java-archive",
    "application/msword",
    "application/pdf",
    "application/vnd.ms-cab-compressed",
    "application/vnd.ms-excel",
    "application/vnd.ms-htmlhelp",
    "application/vnd.ms-office",
    "application/vnd.ms-outlook",
    "application/vnd.ms-powerpoint",
    "application/vnd.ms-tnef",
    "application/vnd.oasis.opendocument.presentation",
    "application/vnd.oasis.opendocument.spreadsheet",
    "application/vnd.oasis.opendocument.text",
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document",
    "application/x-7z-compressed",
    "application/x-bzip2",
    "application/x-dosexec",
    "application/x-executable",
    "application/x-hwp",
    "application/x-iso9660-image",
    "application/x-java-applet",
    "application/x-lzh-compressed",
    "application/x-mach-binary",
    "application/x-ms-shortcut",
    "application/x-ms-wim",
    "application/x-msi",
    "application/x-mswinurl",
    "application/x-rar",
    "application/x-shockwave-flash",
    "application/x-sylk",
    "application/x-tar",
    "application/x-xar",
    "application/x-xz",
    "image/svg+xml",
    "message/rfc822",
    "text/csv",
    "text/html",
    "text/rtf",
    "text/x-msdos-batch",
    "text/x-shellscript",
    "text/xml",
    "video/quicktime"
};

static const char *text_plain_types[] = {
    "uuencoded text"
};

static const char *octet_stream_extensions[] = {
    ".com" // min/max size
};

static const char *text_plain_extensions[] = {
    ".js",
    ".ps1",
    ".vbs",
    ".iqy"};

/*
bat
cmd
csv
hta
htm
html
iqy
js
jse
mht
mhtml
ps1
slk
svg
url
vbe
vbs
wsf
xht
xhtml
xls
*/

void log_it(const char *format, ...) {
    if ( !logging ) {
        return;
    } 
    va_list args;
    va_start(args, format);
    vprintf (format, args);
    printf("\n");
    va_end(args);
}

int check_mime_type(const char *mime_type) {
    for (int i = 0; i < sizeof(mime_types) / sizeof(mime_types[0]); i++)
    {
        if (strcmp(mime_types[i], mime_type) == 0)
        {
            log_it("Matched MIME type: %s", mime_type);
            return 1;
        }
    }
    return 0;
}

int check_text_plain_types(const char *type)
{
    for (int i = 0; i < sizeof(text_plain_types) / sizeof(text_plain_types[0]); i++)
    {
        if (!strncmp(text_plain_types[i], type, strlen(text_plain_types[i])))
        {
            log_it("Matched text/plain type prefix: %s", text_plain_types[i]);
            return 1;
        }
    }
    return 0;
}

int check_extension(const char *list[], int len, const char *filename)
{
    for (int i = 0; i < len; i++)
    {
        const char *dot = strrchr(filename, '.');
        if (!dot)
        {
            return 0;
        }
        if (!strcasecmp(dot, list[i]))
        {
            log_it("Matched file extension: %s", filename);
            return 1;
        }
    }
    return 0;
}

int check_octet_stream_extensions(const char *filename)
{
    const int len = sizeof(octet_stream_extensions) / sizeof(octet_stream_extensions[0]);
    return check_extension(octet_stream_extensions, len, filename);
}

int check_text_plain_extensions(const char *filename)
{
    const int len = sizeof(text_plain_extensions) / sizeof(text_plain_extensions[0]);
    return check_extension(text_plain_extensions, len, filename);
}

const char *get_magic(const char *database, const char *filename, int flags)
{
    magic_t mime_cookie = magic_open(flags);
    if (mime_cookie == NULL)
    {
        last_error_message = "Create magic cookie failed";
        return NULL;
    }
    if (magic_load(mime_cookie, database) != 0)
    {
        magic_close(mime_cookie);
        last_error_message = magic_error(mime_cookie);
        return NULL;
    }
    // magic_close(cookie);
    return magic_file(mime_cookie, filename);
}

int is_supported(const char * database, const char *filename)
{
    log_it("File name: %s", filename);
    const char *mime = get_magic(database, filename, MAGIC_MIME_TYPE);
    if (mime == NULL) {
        return ERROR_OCCURED;
    }
    log_it("MIME type: %s", mime);
    if (check_mime_type(mime))
    {
        return 1;
    }
    if (!strcmp(mime, "application/octet-stream"))
    {
        if (check_octet_stream_extensions(filename))
        {
            return 1;
        }
        //const char *type = get_type(filename);
        //std::cout << "Supported type: " << type << std::endl;
        //return check_octet_stream_types(type);
    }
    if (!strcmp(mime, "text/plain"))
    {
        if (check_text_plain_extensions(filename) ) {
            return 1;
        }
        const char *type  = get_magic(database, filename, 0);
        if (mime == NULL) {
            return ERROR_OCCURED;
        }
        return check_text_plain_types(type);
    }
    return 0;
}
