#include <stdlib.h>
#include <string.h>
#include <sea-turtle.h>
#include <seagrass.h>

#include "private/string.h"

#ifdef TEST
#include <test/cmocka.h>
#endif

int sea_turtle_string_init_string(
        struct sea_turtle_string *const object,
        const struct sea_turtle_string *const other) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    if (!other) {
        return SEA_TURTLE_STRING_ERROR_OTHER_IS_NULL;
    }
    void *data = malloc(other->size);
    if (!data) {
        return SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    *object = *other;
    memcpy(data, other->data, other->size);
    object->data = data;
    return 0;
}

int sea_turtle_string_init(struct sea_turtle_string *const object,
                           const char *const char_ptr,
                           const size_t size,
                           size_t *const out) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    if (!char_ptr) {
        return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_NULL;
    }
    if (!size) {
        return SEA_TURTLE_STRING_ERROR_SIZE_IS_ZERO;
    }
    int error;
    *object = (struct sea_turtle_string) {0};
    size_t count;
    if ((error = sea_turtle_string_is_utf8_sequence(
            char_ptr, size, &count, &object->count))) {
        seagrass_required_true(SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED
                               == error);
        return error;
    }
    if (!count) {
        return SEA_TURTLE_STRING_ERROR_EMPTY_CHAR_SEQUENCE;
    }
    uintmax_t alloc;
    /* add 1 to accommodate the NULL termination char */
    if ((error = seagrass_uintmax_t_add(1, count, &alloc))
        || alloc > SIZE_MAX) {
        seagrass_required_true(
                SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                == error || !error);
        return SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    if ((error = sea_turtle_string_set_size(object, alloc))) {
        seagrass_required_true(
                SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED
                == error);
        return error;
    }
    memcpy(object->data, char_ptr, count);
    /* calculate hashcode */
    const uint8_t *at;
    seagrass_required_true(!sea_turtle_string_first(object, &at));
    do {
        uint32_t code_point;
        seagrass_required_true(!sea_turtle_string_code_point(
                object, at, &code_point));
        object->hash = 31 * object->hash + code_point;
    } while (!(error = sea_turtle_string_next(object, at, &at)));
    seagrass_required_true(SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE
                           == error);
    if (out) {
        *out = count;
    }
    return 0;
}

int sea_turtle_string_invalidate(struct sea_turtle_string *const object) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    free(object->data);
    *object = (struct sea_turtle_string) {0};
    return 0;
}

int sea_turtle_string_is_utf8_sequence(const char *const char_ptr,
                                       const size_t size,
                                       size_t *const out,
                                       uintmax_t *const count) {
    if (!char_ptr) {
        return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_NULL;
    }
    if (!size) {
        return SEA_TURTLE_STRING_ERROR_SIZE_IS_ZERO;
    }
    if (!out) {
        return SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
    }
    /* https://www.rfc-editor.org/rfc/rfc3629#section-4 */
    int error;
    uintmax_t i = 0, o = 0, c = 0;
    const uint8_t *byte = (const uint8_t *) char_ptr;
    while (byte[i] && i < size) {
        seagrass_required_true(!seagrass_uintmax_t_add(1, c, &c));
        /* UTF8-1 */
        if (byte[i] <= 0x7F) {
            if ((error = seagrass_uintmax_t_add(1, i, &i)) || i > size) {
                seagrass_required_true(
                        SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                        == error || !error);
                return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
            }
            continue;
        }
        if ((error = seagrass_uintmax_t_add(1, i, &o)) || o >= size) {
            seagrass_required_true(
                    SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                    == error || !error);
            return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
        }
        /* UTF8-2 */
        if (byte[i] >= 0xC2
            && byte[i] <= 0xDF
            && byte[1 + i] >= 0x80
            && byte[1 + i] <= 0xBF) {
            if ((error = seagrass_uintmax_t_add(2, i, &i)) || i > size) {
                seagrass_required_true(
                        SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                        == error || !error);
                return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
            }
            continue;
        }
        if ((error = seagrass_uintmax_t_add(2, i, &o)) || o >= size) {
            seagrass_required_true(
                    SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                    == error || !error);
            return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
        }
        /* UTF8-3 */
        if ((byte[i] == 0xE0
             && byte[1 + i] >= 0xA0
             && byte[1 + i] <= 0xBF
             && byte[2 + i] >= 0x80
             && byte[2 + i] <= 0xBF)
            || (byte[i] >= 0xE1
                && byte[i] <= 0xEC
                && byte[1 + i] >= 0x80
                && byte[1 + i] <= 0xBF
                && byte[2 + i] >= 0x80
                && byte[2 + i] <= 0xBF)
            || (byte[i] == 0xED
                && byte[1 + i] >= 0x80
                && byte[1 + i] <= 0x9F
                && byte[2 + i] >= 0x80
                && byte[2 + i] <= 0xBF)
            || (byte[i] >= 0xEE
                && byte[i] <= 0xEF
                && byte[1 + i] >= 0x80
                && byte[1 + i] <= 0xBF
                && byte[2 + i] >= 0x80
                && byte[2 + i] <= 0xBF)) {
            if ((error = seagrass_uintmax_t_add(3, i, &i)) || i > size) {
                seagrass_required_true(
                        SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                        == error || !error);
                return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
            }
            continue;
        }
        if ((error = seagrass_uintmax_t_add(3, i, &o)) || o >= size) {
            seagrass_required_true(
                    SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                    == error || !error);
            return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
        }
        /* UTF8-4 */
        if ((byte[i] == 0xF0
             && byte[1 + i] >= 0x90
             && byte[1 + i] <= 0xBF
             && byte[2 + i] >= 0x80
             && byte[2 + i] <= 0xBF
             && byte[3 + i] >= 0x80
             && byte[3 + i] <= 0xBF)
            || (byte[i] >= 0xF1
                && byte[i] <= 0xF3
                && byte[1 + i] >= 0x80
                && byte[1 + i] <= 0xBF
                && byte[2 + i] >= 0x80
                && byte[2 + i] <= 0xBF
                && byte[3 + i] >= 0x80
                && byte[3 + i] <= 0xBF)
            || (byte[i] == 0xF4
                && byte[1 + i] >= 0x80
                && byte[1 + i] <= 0x8F
                && byte[2 + i] >= 0x80
                && byte[2 + i] <= 0xBF
                && byte[3 + i] >= 0x80
                && byte[3 + i] <= 0xBF)) {
            if ((error = seagrass_uintmax_t_add(4, i, &i)) || i > size) {
                seagrass_required_true(
                        SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                        == error || !error);
                return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
            }
            continue;
        }
        return SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
    }
    if (count) {
        *count = c;
    }
    *out = i;
    return 0;
}

int sea_turtle_string_count(const struct sea_turtle_string *const object,
                            uintmax_t *const out) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
    }
    *out = object->count;
    return 0;
}

int sea_turtle_string_compare(const struct sea_turtle_string *const object,
                              const struct sea_turtle_string *const other) {
    seagrass_required_true(object || other);
    if (!other) {
        return (-1);
    }
    if (!object) {
        return 1;
    }
    int result = seagrass_uintmax_t_compare(object->size, other->size);
    if (result) {
        return result;
    }
    result = memcmp(object->data, other->data, object->size);
    if (result < 0) {
        return (-1);
    } else if (result > 0) {
        return 1;
    }
    return 0;
}

int sea_turtle_string_hash(const struct sea_turtle_string *const object,
                           uintmax_t *const out) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
    }
    *out = object->hash;
    return true;
}

int sea_turtle_string_set_size(struct sea_turtle_string *const object,
                               const size_t size) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    uintmax_t new;
    seagrass_required_true(!seagrass_uintmax_t_maximum(
            1, size, &new));
    if (new > SIZE_MAX) {
        return SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    if (new == object->size) {
        return 0;
    }
    uint8_t *data = object->data
                    ? realloc(object->data, new)
                    : malloc(new);
    if (!data) {
        return SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    data[new - 1] = 0;
    object->data = data;
    object->size = new;
    return 0;
}

int sea_turtle_string_first(const struct sea_turtle_string *const object,
                            const uint8_t **const out) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
    }
    *out = object->data;
    return 0;
}

int sea_turtle_string_last(const struct sea_turtle_string *const object,
                           const uint8_t **const out) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
    }
    const uint8_t *end = object->data + object->size - 1;
    seagrass_required_true(!sea_turtle_string_prev(object, end, out));
    return 0;
}

int sea_turtle_string_next(const struct sea_turtle_string *const object,
                           const uint8_t *const at,
                           const uint8_t **const out) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    if (!at) {
        return SEA_TURTLE_STRING_ERROR_AT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
    }
    const uint8_t *const end = object->data + object->size - 1;
    if (at < object->data || end < at) {
        return SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS;
    }
    const uint8_t byte = *at;
    if ((byte & 0xF8) == 0xF0) {
        *out = 4 + at;
    } else if ((byte & 0xF0) == 0xE0) {
        *out = 3 + at;
    } else if ((byte & 0xC0) == 0xC0) {
        *out = 2 + at;
    } else if (!(byte & 0x80)) {
        *out = 1 + at;
    } else {
        return SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
    }
    return end <= *out
        ? SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE
        : 0;
}

int sea_turtle_string_prev(const struct sea_turtle_string *const object,
                           const uint8_t *const at,
                           const uint8_t **const out) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    if (!at) {
        return SEA_TURTLE_STRING_ERROR_AT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
    }
    const uint8_t *const end = object->data + object->size - 1;
    if (at < object->data || end < at) {
        return SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS;
    }
    const uint8_t byte = *at;
    if (((byte & 0xF8) == 0xF0)
        || ((byte & 0xF0) == 0xE0)
        || ((byte & 0xC0) == 0xC0)
        || !(byte & 0x80)) {
        *out = at - 1;
    } else {
        return SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
    }
    size_t i = 4;
    for (; i && (**out & 0xC0) == 0x80; i--, *out -= 1);
    if (!i) {
        return SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
    }
    return *out < object->data
        ? SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE
        : 0;
}

int sea_turtle_string_code_point(const struct sea_turtle_string *const object,
                                 const uint8_t *const at,
                                 uint32_t *const out) {
    if (!object) {
        return SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
    }
    if (!at) {
        return SEA_TURTLE_STRING_ERROR_AT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
    }
    const uint8_t *const end = object->data + object->size - 1;
    if (at < object->data || end < at) {
        return SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS;
    }
    uintmax_t i;
    uint8_t byte = *at;
    if ((byte & 0xF8) == 0xF0) {
        i = 3;
        *out = byte & 0x07;
    } else if ((byte & 0xF0) == 0xE0) {
        i = 2;
        *out = byte & 0x0F;
    } else if ((byte & 0xE0) == 0xC0) {
        i = 1;
        *out = byte & 0x1F;
    } else if (!(byte & 0x80)) {
        i = 0;
        *out = byte & 0x7F;
    } else {
        return SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
    }
    for (uintmax_t o = 0; o < i; o++) {
        byte = *(1 + o + at);
        if ((byte & 0xC0) != 0x80) {
            return SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
        }
        *out <<= 6;
        *out |= byte & 0x3F;
    }
    return 0;
}

