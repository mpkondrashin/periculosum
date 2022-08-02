#ifndef __MAGICCLASS_H__
#define __MAGICCLASS_H__

#include <string>
#include <exception>

#include "build/target/include/magic.h"

//extern unsigned char magic_mgc[];
#include "mgc.h"

class MagicError : public std::exception {

};

class MagicInitError : public MagicError {
    virtual const char* what() const throw()
    {
        return "Magic library init error";
    }
};

class MagicLoadError : public MagicError {
    const char *message;
public:
    MagicLoadError(const char* _message): message(_message) {}
    virtual const char* what() const throw()
    {
        return message;
    }
};


class Magic {
    magic_t cookie;
    int flags; 
public:
    Magic(const char *_database, int _flags = 0) :flags(_flags) {
        cookie = magic_open(flags);
        if (cookie == NULL) {
            throw MagicInitError();
        }
        if (magic_load(cookie, _database) != 0) {
            magic_close(cookie);
            throw MagicLoadError(magic_error(cookie));
        }
    }
    Magic(int _flags = 0) :flags(_flags) {
        cookie = magic_open(flags);
        if (cookie == NULL) {
            throw MagicInitError();
        }
        size_t size = sizeof(magic_mgc);
        void * a[1] = {magic_mgc};
        if (magic_load_buffers(cookie, a, &size, 1) != 0) {
            magic_close(cookie);
            throw MagicLoadError(magic_error(cookie));
        }
    }
    ~Magic() {
        magic_close(cookie);
    }
    const char *Detect(const char *file_name) {
        return magic_file(cookie, file_name);
    }
};

#endif