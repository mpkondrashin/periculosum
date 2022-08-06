/*
 Copyright (C) 2022 Michael Kondrashin — All Rights Reserved
 You may use, distribute and modify this code under the
 terms of the MIT license.
 You should have received a copy of the MIT license with
 this file. If not, please write to: mkondrashin@gmail.com

 Lates version of this file can be found at following URL:
 https://github.com/mpkondrashin/periculosum

 magicclass.h - class Magic declaration
*/

#ifndef __MAGICCLASS_H__
#define __MAGICCLASS_H__

#include <string>
#include <exception>
#include <strings.h>

#include "build/target/include/magic.h"

extern unsigned char magic_mgc[];
extern unsigned int magic_mgc_len;

class MagicException: public std::exception
{
public:
    explicit MagicException(const char* message)
        : msg_(message) {}

    explicit MagicException(const std::string& message)
        : msg_(message) {}

    const char* what() const noexcept override {
       return msg_.c_str();
    }
protected:
    std::string msg_;
};
/*
class MagicError : public std::exception {
};

class MagicInitError : public MagicError {
    virtual const char* what() const noexcept
    {
        return "Magic library init error";
    }
};

class MagicLoadError : public MagicError {
    std::string message;
public:
    MagicLoadError(const char* _message): message(_message) {}
    virtual const char* what() const noexcept
    {
        return message.c_str();
    }
};

*/

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