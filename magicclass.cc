#include "magicclass.h"

Magic::Magic(const char *_database, int _flags = 0) :flags(_flags) {
    cookie = magic_open(flags);
    if (cookie == NULL) {
        throw MagicInitError();
    }
    if (magic_load(cookie, _database) != 0) {
        magic_close(cookie);
        throw MagicLoadError(magic_error(cookie));
    }
}

Magic::Magic(int _flags = 0) :flags(_flags) {
    cookie = magic_open(flags);
    if (cookie == NULL) {
        throw MagicInitError();
    }
    size_t size = magic_mgc_len;
    void * a[1] = {magic_mgc};
    if (magic_load_buffers(cookie, a, &size, 1) != 0) {
        magic_close(cookie);
        throw MagicLoadError(magic_error(cookie));
    }
}