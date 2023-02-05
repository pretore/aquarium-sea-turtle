#include <stdlib.h>
#include <seagrass.h>
#include <sea-turtle.h>

#ifdef TEST

#include <test/cmocka.h>

#endif

bool sea_turtle_integer_init_char_ptr(
        struct sea_turtle_integer *const object,
        const char *const char_ptr) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!char_ptr) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL;
        return false;
    }
    if (mpz_init_set_str(object->mpz, char_ptr, 0)) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED;
        return false;
    }
    return true;
}

bool sea_turtle_integer_init_uintmax_t(
        struct sea_turtle_integer *const object,
        const uintmax_t value) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_init_set_ui(object->mpz, value);
    return true;
}

bool sea_turtle_integer_init_intmax_t(
        struct sea_turtle_integer *const object,
        const intmax_t value) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_init_set_si(object->mpz, value);
    return true;
}

bool sea_turtle_integer_init_integer(
        struct sea_turtle_integer *const object,
        const struct sea_turtle_integer *const other) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
        return false;
    }
    mpz_init_set(object->mpz, other->mpz);
    return true;
}

bool sea_turtle_integer_init(struct sea_turtle_integer *const object) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_init(object->mpz);
    return true;
}

bool sea_turtle_integer_invalidate(struct sea_turtle_integer *const object) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_clear(object->mpz);
    (*object) = (struct sea_turtle_integer) {0};
    return true;
}

bool sea_turtle_integer_set_char_ptr(
        struct sea_turtle_integer *const object,
        const char *const char_ptr) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!char_ptr) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL;
        return false;
    }
    if (mpz_set_str(object->mpz, char_ptr, 0)) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED;
        return false;
    }
    return true;
}

bool sea_turtle_integer_set_uintmax_t(
        struct sea_turtle_integer *const object,
        const uintmax_t value) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_set_ui(object->mpz, value);
    return true;
}

bool sea_turtle_integer_set_intmax_t(
        struct sea_turtle_integer *const object,
        const intmax_t value) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_set_si(object->mpz, value);
    return true;
}

bool sea_turtle_integer_add(struct sea_turtle_integer *const object,
                            const struct sea_turtle_integer *const other) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
        return false;
    }
    mpz_add(object->mpz, object->mpz, other->mpz);
    return true;
}

bool sea_turtle_integer_add_uintmax_t(
        struct sea_turtle_integer *const object,
        const uintmax_t value) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_add_ui(object->mpz, object->mpz, value);
    return true;
}

bool sea_turtle_integer_subtract(struct sea_turtle_integer *const object,
                                 const struct sea_turtle_integer *const other) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
        return false;
    }
    mpz_sub(object->mpz, object->mpz, other->mpz);
    return true;
}

bool sea_turtle_integer_subtract_uintmax_t(
        struct sea_turtle_integer *const object,
        const uintmax_t value) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_sub_ui(object->mpz, object->mpz, value);
    return true;
}

bool sea_turtle_integer_divide(struct sea_turtle_integer *const object,
                               const struct sea_turtle_integer *const divisor,
                               struct sea_turtle_integer *const remainder) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!divisor) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_DIVISOR_IS_NULL;
        return false;
    }
    if (!mpz_cmp_ui(divisor->mpz, 0)) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_DIVISION_BY_ZERO;
        return false;
    }
    if (remainder) {
        mpz_tdiv_qr(object->mpz, remainder->mpz, object->mpz, divisor->mpz);
    } else {
        mpz_tdiv_q(object->mpz, object->mpz, divisor->mpz);
    }
    return true;
}

bool sea_turtle_integer_multiply(struct sea_turtle_integer *const object,
                                 const struct sea_turtle_integer *const other) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
        return false;
    }
    mpz_mul(object->mpz, object->mpz, other->mpz);
    return true;
}

bool sea_turtle_integer_absolute(struct sea_turtle_integer *const object) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_abs(object->mpz, object->mpz);
    return true;
}

bool sea_turtle_integer_negate(struct sea_turtle_integer *const object) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_neg(object->mpz, object->mpz);
    return true;
}

int sea_turtle_integer_compare(const struct sea_turtle_integer *const object,
                               const struct sea_turtle_integer *const other) {
    seagrass_required_true(object || other);
    if (!other) {
        return (-1);
    }
    if (!object) {
        return 1;
    }
    int result = mpz_cmp(object->mpz, other->mpz);
    if (result < 0) {
        return (-1);
    } else if (result > 0) {
        return 1;
    }
    return 0;
}

bool sea_turtle_integer_hash(const struct sea_turtle_integer *const object,
                             uintmax_t *const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
        return false;
    }
    *out = mpz_get_ui(object->mpz);
    return true;
}

bool sea_turtle_integer_and(struct sea_turtle_integer *const object,
                            const struct sea_turtle_integer *const other) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
        return false;
    }
    mpz_and(object->mpz, object->mpz, other->mpz);
    return true;
}

bool sea_turtle_integer_or(struct sea_turtle_integer *const object,
                           const struct sea_turtle_integer *const other) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
        return false;
    }
    mpz_ior(object->mpz, object->mpz, other->mpz);
    return true;
}

bool sea_turtle_integer_not(struct sea_turtle_integer *const object) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_com(object->mpz, object->mpz);
    return true;
}

bool sea_turtle_integer_xor(struct sea_turtle_integer *const object,
                            const struct sea_turtle_integer *const other) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
        return false;
    }
    mpz_xor(object->mpz, object->mpz, other->mpz);
    return true;
}

bool sea_turtle_integer_shift_left(struct sea_turtle_integer *const object,
                                   const uintmax_t nbits) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_mul_2exp(object->mpz, object->mpz, nbits);
    return true;
}

bool sea_turtle_integer_shift_right(struct sea_turtle_integer *const object,
                                    const uintmax_t nbits) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    mpz_tdiv_q_2exp(object->mpz, object->mpz, nbits);
    return true;
}

bool sea_turtle_integer_length(const struct sea_turtle_integer *const object,
                               uintmax_t *const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
        return false;
    }
    *out = mpz_sizeinbase(object->mpz, 2);
    return true;
}

bool sea_turtle_integer_count(const struct sea_turtle_integer *const object,
                              uintmax_t *const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
        return false;
    }
    mpz_t tmp;
    mpz_init(tmp);
    mpz_abs(tmp, object->mpz);
    *out = mpz_popcount(tmp);
    mpz_clear(tmp);
    return true;
}

bool sea_turtle_integer_get(const struct sea_turtle_integer *const object,
                            const uintmax_t at,
                            bool *const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
        return false;
    }
    *out = mpz_tstbit(object->mpz, at);
    return true;
}

bool sea_turtle_integer_set(struct sea_turtle_integer *const object,
                            const uintmax_t at,
                            const bool value) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (value) {
        mpz_setbit(object->mpz, at);
    } else {
        mpz_clrbit(object->mpz, at);
    }
    return true;
}

bool sea_turtle_integer_find(
        const struct sea_turtle_integer *const object,
        const struct sea_turtle_integer_range *const values,
        const bool needle,
        uintmax_t *const out) {
    if (!object) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
        return false;
    }
    uintmax_t length;
    seagrass_required_true(sea_turtle_integer_length(object, &length));
    uintmax_t min = 0, max = length;
    if (values) {
        seagrass_uintmax_t_minimum(values->first, values->last, &min);
        seagrass_uintmax_t_maximum(values->first, values->last, &max);
    }
    if (needle) {
        *out = mpz_scan1(object->mpz, min);
    } else {
        *out = mpz_scan0(object->mpz, min);
    }
    if (max < *out || SIZE_MAX == *out) {
        sea_turtle_error = SEA_TURTLE_INTEGER_ERROR_NEEDLE_NOT_FOUND;
        return false;
    }
    return true;
}
