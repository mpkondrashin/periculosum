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
        magic_close(cookie);
        throw MagicException(magic_error(cookie));
    }
}