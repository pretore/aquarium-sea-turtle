#include <stdlib.h>
#include <string.h>
#include <sea-turtle.h>
#include <seagrass.h>

#include "private/string.h"
#include "test/cmocka.h"

bool sea_turtle_string_init_with_string(
        struct sea_turtle_string *const object,
        const struct sea_turtle_string *const other) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OTHER_IS_NULL;
        return false;
    }
    void *data = malloc(other->size);
    if (!data) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    *object = *other;
    memcpy(data, other->data, other->size);
    object->data = data;
    return true;
}

bool sea_turtle_string_init(struct sea_turtle_string *const object,
                            const char *const char_ptr,
                            const size_t size,
                            size_t *const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!char_ptr) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_NULL;
        return false;
    }
    if (!size) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_SIZE_IS_ZERO;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
        return false;
    }
    *object = (struct sea_turtle_string) {0};
    if (!sea_turtle_string_is_utf8_sequence(
            char_ptr, size, out, &object->count)) {
        seagrass_required_true(SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED
                               == sea_turtle_error);
        return false;
    }
    if (!(*out)) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_EMPTY_CHAR_SEQUENCE;
        return false;
    }
    uintmax_t alloc;
    {
        /* add 1 to accommodate the NULL termination char */
        const bool result = seagrass_uintmax_t_add(1, *out, &alloc);
        if (!result || alloc > SIZE_MAX) {
            seagrass_required_true(
                    SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                    == seagrass_error || result);
            sea_turtle_error = SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED;
            return false;
        }
    }
    if (!sea_turtle_string_set_size(object, alloc)) {
        seagrass_required_true(SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED
                               == sea_turtle_error);
        return false;
    }
    memcpy(object->data, char_ptr, *out);
    return true;
}

bool sea_turtle_string_invalidate(struct sea_turtle_string *const object) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    free(object->data);
    *object = (struct sea_turtle_string) {0};
    return true;
}

bool sea_turtle_string_is_utf8_sequence(const char *const char_ptr,
                                        const size_t size,
                                        size_t *const out,
                                        uintmax_t *const count) {
    if (!char_ptr) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_NULL;
        return false;
    }
    if (!size) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_SIZE_IS_ZERO;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
        return false;
    }
    /* https://www.rfc-editor.org/rfc/rfc3629#section-4 */
    bool result;
    uintmax_t i = 0, o = 0, c = 0;
    const uint8_t *byte = (const uint8_t *) char_ptr;
    while (byte[i] && i < size) {
        seagrass_required_true(seagrass_uintmax_t_add(1, c, &c));
        /* UTF8-1 */
        if (byte[i] <= 0x7F) {
            if (!(result = seagrass_uintmax_t_add(1, i, &i))
                || i > size) {
                seagrass_required_true(
                        SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                        == seagrass_error || result);
                sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
                return false;
            }
            continue;
        }
        if (!(result = seagrass_uintmax_t_add(1, i, &o))
            || o >= size) {
            seagrass_required_true(
                    SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                    == seagrass_error || result);
            sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
            return false;
        }
        /* UTF8-2 */
        if (byte[i] >= 0xC2
            && byte[i] <= 0xDF
            && byte[1 + i] >= 0x80
            && byte[1 + i] <= 0xBF) {
            if (!(result = seagrass_uintmax_t_add(2, i, &i))
                || i > size) {
                seagrass_required_true(
                        SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                        == seagrass_error || result);
                sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
                return false;
            }
            continue;
        }
        if (!(result = seagrass_uintmax_t_add(2, i, &o))
            || o >= size) {
            seagrass_required_true(
                    SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                    == seagrass_error || result);
            sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
            return false;
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
            if (!(result = seagrass_uintmax_t_add(3, i, &i))
                || i > size) {
                seagrass_required_true(
                        SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                        == seagrass_error || result);
                sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
                return false;
            }
            continue;
        }
        if (!(result = seagrass_uintmax_t_add(3, i, &o))
            || o >= size) {
            seagrass_required_true(
                    SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                    == seagrass_error || result);
            sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
            return false;
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
            if (!(result = seagrass_uintmax_t_add(4, i, &i))
                || i > size) {
                seagrass_required_true(
                        SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                        == seagrass_error || result);
                sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
                return false;
            }
            continue;
        }
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED;
        return false;
    }
    if (count) {
        *count = c;
    }
    *out = i;
    return true;
}

bool sea_turtle_string_count(const struct sea_turtle_string *const object,
                             uintmax_t *const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
        return false;
    }
    *out = object->count;
    return true;
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

bool sea_turtle_string_set_size(struct sea_turtle_string *const object,
                                const size_t size) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    uintmax_t new;
    seagrass_required_true(seagrass_uintmax_t_maximum(
            1, size, &new));
    if (new > SIZE_MAX) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    if (new == object->size) {
        return true;
    }
    uint8_t *data = object->data
                    ? realloc(object->data, new)
                    : malloc(new);
    if (!data) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    data[new - 1] = 0;
    object->data = data;
    object->size = new;
    return true;
}

bool sea_turtle_string_first(const struct sea_turtle_string *const object,
                             const uint8_t **const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
        return false;
    }
    *out = object->data;
    return true;
}

bool sea_turtle_string_last(const struct sea_turtle_string *const object,
                            const uint8_t **const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
        return false;
    }
    const uint8_t *end = object->data + object->size - 1;
    seagrass_required_true(sea_turtle_string_prev(object, end, out));
    return true;
}

bool sea_turtle_string_next(const struct sea_turtle_string *const object,
                            const uint8_t *const at,
                            const uint8_t **const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!at) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
        return false;
    }
    const uint8_t *const end = object->data + object->size - 1;
    if (at < object->data || end < at) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS;
        return false;
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
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
        return false;
    }
    if (end <= *out) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE;
        return false;
    }
    return true;
}

bool sea_turtle_string_prev(const struct sea_turtle_string *const object,
                            const uint8_t *const at,
                            const uint8_t **const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!at) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
        return false;
    }
    const uint8_t *const end = object->data + object->size - 1;
    if (at < object->data || end < at) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS;
        return false;
    }
    const uint8_t byte = *at;
    if (((byte & 0xF8) == 0xF0)
        || ((byte & 0xF0) == 0xE0)
        || ((byte & 0xC0) == 0xC0)
        || !(byte & 0x80)) {
        *out = at - 1;
    } else {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
        return false;
    }
    size_t i = 4;
    for (; i && (**out & 0xC0) == 0x80; i--, *out -= 1);
    if (!i) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
        return false;
    }
    if (*out < object->data) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE;
        return false;
    }
    return true;
}

bool sea_turtle_string_code_point(const struct sea_turtle_string *const object,
                                  const uint8_t *const at,
                                  uint32_t *const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!at) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_OUT_IS_NULL;
        return false;
    }
    const uint8_t *const end = object->data + object->size - 1;
    if (at < object->data || end < at) {
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS;
        return false;
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
        sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
        return false;
    }
    for (uintmax_t o = 0; o < i; o++) {
        byte = *(1 + o + at);
        if ((byte & 0xC0) != 0x80) {
            sea_turtle_error = SEA_TURTLE_STRING_ERROR_AT_IS_INVALID;
            return false;
        }
        *out <<= 6;
        *out |= byte & 0x3F;
    }
    return true;
}

