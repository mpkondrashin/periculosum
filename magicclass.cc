/*
 Copyright (C) 2022 Michael Kondrashin — All Rights Reserved
 You may use, distribute and modify this code under the
 terms of the MIT license.
 You should have received a copy of the MIT license with
 this file. If not, please write to: mkondrashin@gmail.com

 Lates version of this file can be found at following URL:
 https://github.com/mpkondrashin/periculosum

 magicclass.cc - class Magic implementation
*/

#include "magicclass.h"

Magic::Magic(const char *_database, int _flags) :flags(_flags) {
    cookie = magic_open(flags);
    if (cookie == NULL) {
        throw MagicException("Magic library init error");
    }
    if (magic_load(cookie, _database) != 0) {
        magic_close(cookie);
        throw MagicException(magic_error(cookie));
    }
}

Magic::Magic(int _flags) :flags(_flags) {
    cookie = magic_open(flags);
    if (cookie == NULL) {
        throw MagicException("Magic library init error");
    }
    size_t size = magic_mgc_len;
    void * a[1] = {magic_mgc};
    if (magic_load_buffers(cookie, a, &size, 1) != 0) {
        MagicException exc(magic_error(cookie));
        magic_close(cookie);
        throw exc;
    }
}