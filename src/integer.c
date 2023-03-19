#include <stdlib.h>
#include <seagrass.h>
#include <sea-turtle.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

int sea_turtle_integer_init_char_ptr(
        struct sea_turtle_integer *const object,
        const char *const char_ptr) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!char_ptr) {
        return SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL;
    }
    return mpz_init_set_str(object->mpz, char_ptr, 0)
        ? SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED
        : 0;
}

int sea_turtle_integer_init_uintmax_t(
        struct sea_turtle_integer *const object,
        const uintmax_t value) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_init_set_ui(object->mpz, value);
    return 0;
}

int sea_turtle_integer_init_intmax_t(
        struct sea_turtle_integer *const object,
        const intmax_t value) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_init_set_si(object->mpz, value);
    return 0;
}

int sea_turtle_integer_init_integer(
        struct sea_turtle_integer *const object,
        const struct sea_turtle_integer *const other) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!other) {
        return SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
    }
    mpz_init_set(object->mpz, other->mpz);
    return 0;
}

int sea_turtle_integer_init(struct sea_turtle_integer *const object) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_init(object->mpz);
    return 0;
}

int sea_turtle_integer_invalidate(struct sea_turtle_integer *const object) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_clear(object->mpz);
    *object = (struct sea_turtle_integer) {0};
    return 0;
}

int sea_turtle_integer_set_char_ptr(
        struct sea_turtle_integer *const object,
        const char *const char_ptr) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!char_ptr) {
        return SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL;
    }
    return mpz_set_str(object->mpz, char_ptr, 0)
        ? SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED
        : 0;
}

int sea_turtle_integer_set_uintmax_t(
        struct sea_turtle_integer *const object,
        const uintmax_t value) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_set_ui(object->mpz, value);
    return 0;
}

int sea_turtle_integer_set_intmax_t(
        struct sea_turtle_integer *const object,
        const intmax_t value) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_set_si(object->mpz, value);
    return 0;
}

int sea_turtle_integer_set_integer(
        struct sea_turtle_integer *const object,
        const struct sea_turtle_integer *const other) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!other) {
        return SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
    }
    mpz_set(object->mpz, other->mpz);
    return 0;
}

int sea_turtle_integer_add(struct sea_turtle_integer *const object,
                           const struct sea_turtle_integer *const other) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!other) {
        return SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
    }
    mpz_add(object->mpz, object->mpz, other->mpz);
    return 0;
}

int sea_turtle_integer_add_uintmax_t(
        struct sea_turtle_integer *const object,
        const uintmax_t value) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_add_ui(object->mpz, object->mpz, value);
    return 0;
}

int sea_turtle_integer_subtract(
        struct sea_turtle_integer *const object,
        const struct sea_turtle_integer *const other) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!other) {
        return SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
    }
    mpz_sub(object->mpz, object->mpz, other->mpz);
    return 0;
}

int sea_turtle_integer_subtract_uintmax_t(
        struct sea_turtle_integer *const object,
        const uintmax_t value) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_sub_ui(object->mpz, object->mpz, value);
    return 0;
}

int sea_turtle_integer_divide(struct sea_turtle_integer *const object,
                              const struct sea_turtle_integer *const divisor,
                              struct sea_turtle_integer *const remainder) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!divisor) {
        return SEA_TURTLE_INTEGER_ERROR_DIVISOR_IS_NULL;
    }
    if (!mpz_cmp_ui(divisor->mpz, 0)) {
        return SEA_TURTLE_INTEGER_ERROR_DIVISION_BY_ZERO;
    }
    if (remainder) {
        mpz_tdiv_qr(object->mpz, remainder->mpz, object->mpz, divisor->mpz);
    } else {
        mpz_tdiv_q(object->mpz, object->mpz, divisor->mpz);
    }
    return 0;
}

int sea_turtle_integer_multiply(struct sea_turtle_integer *const object,
                                const struct sea_turtle_integer *const other) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!other) {
        return SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
    }
    mpz_mul(object->mpz, object->mpz, other->mpz);
    return 0;
}

int sea_turtle_integer_absolute(struct sea_turtle_integer *const object) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_abs(object->mpz, object->mpz);
    return 0;
}

int sea_turtle_integer_negate(struct sea_turtle_integer *const object) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_neg(object->mpz, object->mpz);
    return 0;
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

int sea_turtle_integer_hash(const struct sea_turtle_integer *const object,
                            uintmax_t *const out) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
    }
    *out = mpz_get_ui(object->mpz);
    return 0;
}

int sea_turtle_integer_and(struct sea_turtle_integer *const object,
                           const struct sea_turtle_integer *const other) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!other) {
        return SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
    }
    mpz_and(object->mpz, object->mpz, other->mpz);
    return 0;
}

int sea_turtle_integer_or(struct sea_turtle_integer *const object,
                          const struct sea_turtle_integer *const other) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!other) {
        return SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
    }
    mpz_ior(object->mpz, object->mpz, other->mpz);
    return 0;
}

int sea_turtle_integer_not(struct sea_turtle_integer *const object) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_com(object->mpz, object->mpz);
    return 0;
}

int sea_turtle_integer_xor(struct sea_turtle_integer *const object,
                           const struct sea_turtle_integer *const other) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!other) {
        return SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL;
    }
    mpz_xor(object->mpz, object->mpz, other->mpz);
    return 0;
}

int sea_turtle_integer_shift_left(struct sea_turtle_integer *const object,
                                  const uintmax_t count) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_mul_2exp(object->mpz, object->mpz, count);
    return 0;
}

int sea_turtle_integer_shift_right(struct sea_turtle_integer *const object,
                                   const uintmax_t count) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    mpz_tdiv_q_2exp(object->mpz, object->mpz, count);
    return 0;
}

int sea_turtle_integer_length(const struct sea_turtle_integer *const object,
                              uintmax_t *const out) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
    }
    *out = mpz_sizeinbase(object->mpz, 2);
    return 0;
}

int sea_turtle_integer_count(const struct sea_turtle_integer *const object,
                             uintmax_t *const out) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
    }
    mpz_t tmp;
    mpz_init(tmp);
    mpz_abs(tmp, object->mpz);
    *out = mpz_popcount(tmp);
    mpz_clear(tmp);
    return 0;
}

int sea_turtle_integer_get(const struct sea_turtle_integer *const object,
                           const uintmax_t at,
                           bool *const out) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
    }
    *out = mpz_tstbit(object->mpz, at);
    return 0;
}

int sea_turtle_integer_set(struct sea_turtle_integer *const object,
                           const uintmax_t at,
                           const bool value) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (value) {
        mpz_setbit(object->mpz, at);
    } else {
        mpz_clrbit(object->mpz, at);
    }
    return 0;
}

int sea_turtle_integer_find(
        const struct sea_turtle_integer *const object,
        const struct sea_turtle_integer_range *const values,
        const bool needle,
        uintmax_t *const out) {
    if (!object) {
        return SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL;
    }
    if (!out) {
        return SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL;
    }
    uintmax_t length;
    seagrass_required_true(!sea_turtle_integer_length(object, &length));
    uintmax_t min = 0, max = length;
    if (values) {
        seagrass_required_true(!seagrass_uintmax_t_minimum(
                values->first, values->last, &min));
        seagrass_required_true(!seagrass_uintmax_t_maximum(
                values->first, values->last, &max));
    }
    if (needle) {
        *out = mpz_scan1(object->mpz, min);
    } else {
        *out = mpz_scan0(object->mpz, min);
    }
    return max < *out || SIZE_MAX == *out
        ? SEA_TURTLE_INTEGER_ERROR_NEEDLE_NOT_FOUND
        : 0;
}
