/*
 Copyright (C) 2022 Michael Kondrashin — All Rights Reserved
 You may use, distribute and modify this code under the
 terms of the MIT license.
 You should have received a copy of the MIT license with
 this file. If not, please write to: mkondrashin@gmail.com

 Lates version of this file can be found at following URL:
 https://github.com/mpkondrashin/periculosum

 process.cc - process file and return whenever it is supported by DDAn
*/

#include "process.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "magicclass.h"

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
    "application/mac-binhex40",
    "application/msword",
    "application/pdf",
    "application/vnd.microsoft.portable-executable",
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
    "application/vnd.rar",
    "application/vnd.symbian.install",
    "application/x-7z-compressed",
    "application/x-ace-compressed",
    "application/x-arc",
    "application/x-arj",
    "application/x-bzip2",
    "application/x-chrome-extension",
    "application/x-dosexec",
    "application/x-executable",
    "application/x-hwp",
    "application/x-iso9660-image",
    "application/x-java-applet",
    "application/x-lzh-compressed",
    "application/x-lzip",
    "application/x-mach-binary",
    "application/x-ms-ne-executable",
    "application/x-ms-shortcut",
    "application/x-ms-wim",
    "application/x-msi",
    "application/x-mswinurl",
    "application/x-pie-executable",
    "application/x-rar",
    "application/x-shockwave-flash",
    "application/x-stuffit",
    "application/x-sylk",
    "application/x-tar",
    "application/x-xar",
    "application/x-xz",
    "application/zip",
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
    "com" // min/max size
};

/*
static const char *text_plain_extensions[] = {
    "js",
    "ps1",
    "vbs",
    "iqy",
    "vbe"};
*/

#define MAX_EXT_LEN 6

static const char *extensions[] = {
    "bat",
    "cmd",
    "csv",
    "hta",
    "htm",
    "html",
    "iqy",
    "js",
    "jse",
    "mht",
    "mhtml",
    "ps1",
    "shtm",
    "shtml",
    "slk",
    "svg",
    "url",
    "vbe",
    "vbs",
    "wsf",
    "xht",
    "xhtml",
    "xls"
};

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

int binary_search(const char *needle, const char *haystack[], int haystack_length)
{
    int i = 0, j = haystack_length - 1;
    while (i <= j) {
        int k = i + ((j - i) / 2);
        int d = strcmp(needle, haystack[k]);
        if ( d == 0 ) {
            return 1;
        }
        if ( d > 0 ) {
            i = k + 1;
        } else {
            j = k - 1;
        }
    }
    return 0;
}

int check_mime_type(const char *mime_type) {
    return binary_search(mime_type, mime_types, sizeof(mime_types) / sizeof(mime_types[0]));
}

int check_text_plain_types(const char *type)
{
    for (int i = 0; i < sizeof(text_plain_types) / sizeof(text_plain_types[0]); i++)
    {
        if (!strncmp(text_plain_types[i], type, strlen(text_plain_types[i])))
        {
            log_it("Matched text/plain type: %s", text_plain_types[i]);
            return 1;
        }
    }
    return 0;
}

int check_extension(const char *list[], int len, const char *filename)
{

    const char *dot = strrchr(filename, '.');
    if (!dot) return 0;
    dot++;
    char ext[MAX_EXT_LEN];
    for(int i = 0; ; i++){
        ext[i] = tolower(dot[i]);
        if ( dot[i] == '\0' )
            break;
        if ( i == MAX_EXT_LEN-1 ) {
            ext[MAX_EXT_LEN-1] = 0;
            break;
        }
    }
    return binary_search(ext, list, len);
    /*for (int i = 0; i < len; i++)
    {
        if (!strcasecmp(dot+1, list[i]))
        {
            log_it("Matched file extension: %s", filename);
            return 1;
        }
    }
    return 0;*/
}

int check_octet_stream_extensions(const char *filename)
{
    const int len = sizeof(octet_stream_extensions) / sizeof(octet_stream_extensions[0]);
    return check_extension(octet_stream_extensions, len, filename);
}
/*
int check_text_plain_extensions(const char *filename)
{
    const int len = sizeof(text_plain_extensions) / sizeof(text_plain_extensions[0]);
    return check_extension(text_plain_extensions, len, filename);
}
*/
/*
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
*/

int is_supported(const char *filename, const char *trueFilename, Magic *magicMime, Magic *magicType)
{
    log_it("File name: %s", filename);
    log_it("True file name: %s", trueFilename);
    const int len = sizeof(extensions) / sizeof(extensions[0]);
    int rc = check_extension(extensions, len, trueFilename);
    if (rc) {
        log_it("Matched file extension: %s", trueFilename);
        return 1;
    }
    const char *mime = magicMime->Detect(filename);
    log_it("Detected MIME type: %s", mime);
    if (check_mime_type(mime))
    {
        log_it("Matched MIME type: %s", mime);
        return 1;
    }
    if (!strcmp(mime, "application/octet-stream"))
    {
        if (check_octet_stream_extensions(trueFilename))
        {
            log_it("Matched octet-stream extension: %s", trueFilename);
            return 1;
        }
    }
    if (!strcmp(mime, "text/plain"))
    {
        const char *type  = magicType->Detect(filename);
        return check_text_plain_types(type);
    }
    return 0;
}
