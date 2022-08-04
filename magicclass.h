#ifndef __MAGICCLASS_H__
#define __MAGICCLASS_H__

#include <string>
#include <exception>
#include <strings.h>

#include "build/target/include/magic.h"

extern unsigned char magic_mgc[];
extern unsigned int magic_mgc_len;

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
    MagicLoadError(const char* _message): message(strdup(_message)) {}
    ~MagicLoadError(){
        delete message;
    }
    virtual const char* what() const throw()
    {
        return message;
    }
};


class Magic {
    magic_t cookie;
    int flags; 
public:
    Magic(const char *_database, int _flags = 0);
    Magic(int _flags = 0);
    ~Magic() {
        magic_close(cookie);
    }
    const char *Detect(const char *file_name) {
        return magic_file(cookie, file_name);
    }
};

#endif