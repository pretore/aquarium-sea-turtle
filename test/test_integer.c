#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <time.h>
#include <sea-turtle.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_invalidate(NULL),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_invalidate(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_init_char_ptr_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_init_char_ptr(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_init_char_ptr_error_on_char_ptr_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_init_char_ptr((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL);
}

static void
check_init_char_ptr_error_on_char_ptr_is_malformed(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(
            sea_turtle_integer_init_char_ptr(
                    &object, "28761236187720391aa"),
            SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED);
}

static void check_init_char_ptr(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(sea_turtle_integer_init_char_ptr(
            &object,
            "826221238914710294871294812617285631892198412643162192184281736249"
            "634961294639146710643197329057023197493217781236481246031640871753"
            "298171906431023762174693164013471937498357293653296589726387162386"
            "128736781263012746398610461309483691386490123649817259873297592837"
            "932657821568732123423425427617843198352371433532824595485248132"), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_init_uintmax_t_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_init_uintmax_t(NULL, 0),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_init_uintmax_t(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&object, 8972), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_init_intmax_t_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_init_intmax_t(NULL, 2134),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_init_intmax_t(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(sea_turtle_integer_init_intmax_t(&object, -2321), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_init_integer_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_init_integer(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_init_integer_error_on_other_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_init_integer((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL);
}

static void check_init_integer(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 98123), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_integer(&o, &i), 0);
    assert_int_equal(mpz_get_ui(o.mpz), 98123);
    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_init_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_init(NULL),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_init(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(sea_turtle_integer_init(&object), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_set_char_ptr_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_set_char_ptr(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_set_char_ptr_error_on_char_ptr_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_set_char_ptr((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL);
}

static void
check_set_char_ptr_error_on_char_ptr_is_malformed(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(sea_turtle_integer_init(&object), 0);
    assert_int_equal(
            sea_turtle_integer_set_char_ptr(
                    &object, "28761236187720391aa"),
            SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED);
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_set_char_ptr(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(sea_turtle_integer_init(&object), 0);
    assert_int_equal(sea_turtle_integer_set_char_ptr(
            &object,
            "826221238914710294871294812617285631892198412643162192184281736249"
            "634961294639146710643197329057023197493217781236481246031640871753"
            "298171906431023762174693164013471937498357293653296589726387162386"
            "128736781263012746398610461309483691386490123649817259873297592837"
            "932657821568732123423425427617843198352371433532824595485248132"), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_set_uintmax_t_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_set_uintmax_t(NULL, 0),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_set_uintmax_t(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(sea_turtle_integer_init(&object), 0);
    assert_int_equal(sea_turtle_integer_set_uintmax_t(&object, 8972), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_set_intmax_t_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_set_intmax_t(NULL, 2134),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_set_intmax_t(void **state) {
    struct sea_turtle_integer object = {};
    assert_int_equal(sea_turtle_integer_init(&object), 0);
    assert_int_equal(sea_turtle_integer_set_intmax_t(&object, -2321), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_set_integer_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_set_integer(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_set_integer_error_on_other_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_set_integer((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL);
}

static void check_set_integer(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 98123), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 47248), 0);
    assert_int_equal(sea_turtle_integer_set_integer(&i, &o), 0);
    assert_int_equal(mpz_get_ui(i.mpz), 47248);
    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_add_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_add(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_add_error_on_other_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_add((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL);
}

static void check_add(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 72163), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 21786), 0);
    assert_int_equal(sea_turtle_integer_add(&i, &o), 0);
    assert_int_equal(mpz_get_si(i.mpz), 93949);
    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_add_uintmax_t_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_add_uintmax_t(NULL, 72163),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_add_uintmax_t(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 72163), 0);
    assert_int_equal(sea_turtle_integer_add_uintmax_t(&i, 21786), 0);
    assert_int_equal(mpz_get_si(i.mpz), 93949);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_subtract_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_subtract(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_subtract_error_on_other_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_subtract((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL);
}

static void check_subtract(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 72163), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 21786), 0);
    assert_int_equal(sea_turtle_integer_subtract(&i, &o), 0);
    assert_int_equal(mpz_get_si(i.mpz), 50377);
    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_subtract_uintmax_t_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_subtract_uintmax_t(NULL, 21786),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_subtract_uintmax_t(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 72163), 0);
    assert_int_equal(sea_turtle_integer_subtract_uintmax_t(&i, 21786), 0);
    assert_int_equal(mpz_get_si(i.mpz), 50377);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_divide_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_divide(NULL, (void *) 1, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_divide_error_on_divisor_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_divide((void *) 1, NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_DIVISOR_IS_NULL);
}

static void check_divide_error_on_divide_by_zero(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 1000), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 0), 0);
    assert_int_equal(
            sea_turtle_integer_divide(&i, &o, NULL),
            SEA_TURTLE_INTEGER_ERROR_DIVISION_BY_ZERO);
    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_divide(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 1000), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 4), 0);
    assert_int_equal(sea_turtle_integer_divide(&i, &o, NULL), 0);
    assert_int_equal(mpz_get_si(i.mpz), 250);
    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 1000), 0);
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 3), 0);
    struct sea_turtle_integer p = {};
    assert_int_equal(sea_turtle_integer_init(&p), 0);
    assert_int_equal(sea_turtle_integer_divide(&i, &o, &p), 0);
    assert_int_equal(mpz_get_si(i.mpz), 333);
    assert_int_equal(mpz_get_si(p.mpz), 1);
    assert_int_equal(sea_turtle_integer_invalidate(&p), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_multiply_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_multiply(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_multiply_error_on_other_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_multiply((void *) 1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL);
}

static void check_multiply(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 10), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_intmax_t(&o, -10), 0);
    assert_int_equal(sea_turtle_integer_multiply(&i, &o), 0);
    assert_int_equal(mpz_get_si(i.mpz), -100);
    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_absolute_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_absolute(NULL),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_absolute(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_intmax_t(&i, -1), 0);
    assert_int_equal(mpz_get_si(i.mpz), -1);
    assert_int_equal(sea_turtle_integer_absolute(&i), 0);
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_int_equal(sea_turtle_integer_absolute(&i), 0);
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_negate_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_negate(NULL),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_negate(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_intmax_t(&i, -1), 0);
    assert_int_equal(mpz_get_si(i.mpz), -1);
    assert_int_equal(sea_turtle_integer_negate(&i), 0);
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_int_equal(sea_turtle_integer_negate(&i), 0);
    assert_int_equal(mpz_get_si(i.mpz), -1);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_compare(void **state) {
    struct sea_turtle_integer i;
    assert_int_equal(sea_turtle_integer_init(&i), 0);
    struct sea_turtle_integer o;
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 1), 0);

    assert_int_equal((-1), sea_turtle_integer_compare(&i, &o));
    assert_int_equal((-1), sea_turtle_integer_compare(&i, NULL));
    assert_int_equal((-1), sea_turtle_integer_compare(&o, NULL));
    assert_int_equal(0, sea_turtle_integer_compare(&i, &i));
    assert_int_equal(0, sea_turtle_integer_compare(&o, &o));
    assert_int_equal(1, sea_turtle_integer_compare(&o, &i));
    assert_int_equal(1, sea_turtle_integer_compare(NULL, &i));
    assert_int_equal(1, sea_turtle_integer_compare(NULL, &o));

    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);

    abort_is_overridden = true;
    expect_function_call(cmocka_test_abort);
    sea_turtle_integer_compare(NULL, NULL);
    abort_is_overridden = false;
}

static void check_hash(void **state) {
    srand(time(NULL));
    struct sea_turtle_integer object;
    assert_int_equal(sea_turtle_integer_init_uintmax_t(
            &object, (1 + rand()) % (UINTMAX_MAX - 1)), 0);
    uintmax_t code;
    assert_int_equal(sea_turtle_integer_hash(&object, &code), 0);
    assert_int_not_equal(code, 0);
    assert_int_equal(sea_turtle_integer_invalidate(&object), 0);
}

static void check_and_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_and(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_and_error_on_other_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_and((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL);
}

static void check_and(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init(&i), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 1), 0);

    assert_int_equal(sea_turtle_integer_and(&o, &o), 0);
    assert_int_equal(mpz_get_si(o.mpz), 1);
    assert_int_equal(sea_turtle_integer_and(&i, &o), 0);
    assert_int_equal(mpz_get_si(i.mpz), 0);
    assert_int_equal(sea_turtle_integer_and(&o, &i), 0);
    assert_int_equal(mpz_get_si(o.mpz), 0);
    assert_int_equal(sea_turtle_integer_and(&i, &i), 0);
    assert_int_equal(mpz_get_si(i.mpz), 0);

    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_or_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_or(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_or_error_on_other_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_or((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL);
}

static void check_or(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init(&i), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 1), 0);

    assert_int_equal(sea_turtle_integer_or(&o, &o), 0);
    assert_int_equal(mpz_get_si(o.mpz), 1);
    assert_int_equal(sea_turtle_integer_or(&o, &i), 0);
    assert_int_equal(mpz_get_si(o.mpz), 1);
    assert_int_equal(sea_turtle_integer_or(&i, &o), 0);
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
    assert_int_equal(sea_turtle_integer_init(&i), 0);
    assert_int_equal(sea_turtle_integer_or(&i, &i), 0);
    assert_int_equal(mpz_get_si(i.mpz), 0);

    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_not_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_not(NULL),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_not(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 1), 0);
    assert_int_equal(sea_turtle_integer_not(&i), 0);
    assert_int_equal(mpz_get_si(i.mpz), -2);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_xor_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_xor(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_xor_error_on_other_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_xor((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL);
}

static void check_xor(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init(&i), 0);
    struct sea_turtle_integer o = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&o, 1), 0);

    assert_int_equal(sea_turtle_integer_xor(&i, &o), 0);
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_int_equal(sea_turtle_integer_xor(&i, &o), 0);
    assert_int_equal(mpz_get_si(i.mpz), 0);

    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
    assert_int_equal(sea_turtle_integer_invalidate(&o), 0);
}

static void check_shift_left_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_shift_left(NULL, 0),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_shift_left(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 1), 0);
    assert_int_equal(1, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_shift_left(&i, 10), 0);
    assert_int_equal(1024, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
    assert_int_equal(sea_turtle_integer_init_intmax_t(&i, -1), 0);
    assert_int_equal(-1, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_shift_left(&i, 10), 0);
    assert_int_equal(-1024, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_shift_right_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_shift_right(NULL, 0),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_shift_right(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 1024), 0);
    assert_int_equal(1024, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_shift_right(&i, 10), 0);
    assert_int_equal(1, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
    assert_int_equal(sea_turtle_integer_init_intmax_t(&i, -1024), 0);
    assert_int_equal(-1024, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_shift_right(&i, 10), 0);
    assert_int_equal(-1, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_length_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_length(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_length_error_on_out_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_length((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL);
}

static void check_length(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 1024), 0);
    assert_int_equal(1024, mpz_get_si(i.mpz));
    uintmax_t length;
    assert_int_equal(sea_turtle_integer_length(&i, &length), 0);
    assert_int_equal(11, length);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
    assert_int_equal(sea_turtle_integer_init_intmax_t(&i, -2048), 0);
    assert_int_equal(-2048, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_length(&i, &length), 0);
    assert_int_equal(12, length);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_count_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_count(NULL, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_count_error_on_out_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_count((void *)1, NULL),
            SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL);
}

static void check_count(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 1024), 0);
    assert_int_equal(1024, mpz_get_si(i.mpz));
    uintmax_t count;
    assert_int_equal(sea_turtle_integer_count(&i, &count), 0);
    assert_int_equal(1, count);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 255), 0);
    assert_int_equal(255, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_count(&i, &count), 0);
    assert_int_equal(8, count);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_get_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_get(NULL, 0, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_get_error_on_out_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_get((void *)1, 0, NULL),
            SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL);
}

static void check_get(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, 1025), 0);
    bool value;
    assert_int_equal(sea_turtle_integer_get(&i, 0, &value), 0);
    assert_true(value);
    assert_int_equal(sea_turtle_integer_get(&i, 1024, &value), 0);
    assert_false(value);
    assert_int_equal(sea_turtle_integer_get(&i, 10, &value), 0);
    assert_true(value);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
    assert_int_equal(sea_turtle_integer_init_uintmax_t(&i, -1025), 0);
    assert_int_equal(sea_turtle_integer_get(&i, 1024, &value), 0);
    assert_false(value);
    /* twos compliment representation for a negative number */
    for (uintmax_t o = 0; o < 10; o++) {
        assert_int_equal(sea_turtle_integer_get(&i, o, &value), 0);
        assert_true(value);
    }
    assert_int_equal(sea_turtle_integer_get(&i, 10, &value), 0);
    assert_false(value);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_set_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_set(NULL, 0, false),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_set(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init(&i), 0);
    assert_int_equal(0, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_set(&i, 10, true), 0);
    bool value;
    assert_int_equal(sea_turtle_integer_get(&i, 10, &value), 0);
    assert_true(value);
    assert_int_equal(sea_turtle_integer_set(&i, 0, true), 0);
    assert_int_equal(sea_turtle_integer_negate(&i), 0);
    /* twos compliment representation for a negative number */
    assert_int_equal(sea_turtle_integer_get(&i, 10, &value), 0);
    assert_false(value);
    assert_int_equal(sea_turtle_integer_negate(&i), 0);
    assert_int_equal(sea_turtle_integer_set(&i, 1024, false), 0);
    assert_int_equal(sea_turtle_integer_get(&i, 1024, &value), 0);
    assert_false(value);
    assert_int_equal(sea_turtle_integer_set(&i, 10, false), 0);
    assert_int_equal(sea_turtle_integer_get(&i, 10, &value), 0);
    assert_false(value);
    assert_int_equal(1, mpz_get_si(i.mpz));
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_find_error_on_object_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_find(NULL, (void *) 1, false, (void *) 1),
            SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL);
}

static void check_find_error_on_out_is_null(void **state) {
    assert_int_equal(
            sea_turtle_integer_find((void *) 1, (void *) 1, true, NULL),
            SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL);
}

static void check_find_error_on_needle_not_found(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init(&i), 0);
    uintmax_t at;
    assert_int_equal(
            sea_turtle_integer_find(&i, NULL, true, &at),
            SEA_TURTLE_INTEGER_ERROR_NEEDLE_NOT_FOUND);
    assert_int_equal(sea_turtle_integer_set(&i, 212, true), 0);
    struct sea_turtle_integer_range values = {
            .first = 19,
            .last = 100
    };
    assert_int_equal(
            sea_turtle_integer_find(&i, &values, true, &at),
            SEA_TURTLE_INTEGER_ERROR_NEEDLE_NOT_FOUND);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

static void check_find(void **state) {
    struct sea_turtle_integer i = {};
    assert_int_equal(sea_turtle_integer_init(&i), 0);
    assert_int_equal(sea_turtle_integer_set(&i, 1023, true), 0);
    uintmax_t at;
    assert_int_equal(sea_turtle_integer_find(&i, NULL, false, &at), 0);
    assert_int_equal(0, at);
    assert_int_equal(sea_turtle_integer_find(&i, NULL, true, &at), 0);
    assert_int_equal(1023, at);
    assert_int_equal(sea_turtle_integer_invalidate(&i), 0);
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_invalidate_error_on_object_is_null),
            cmocka_unit_test(check_invalidate),
            cmocka_unit_test(check_init_char_ptr_error_on_object_is_null),
            cmocka_unit_test(check_init_char_ptr_error_on_char_ptr_is_null),
            cmocka_unit_test(check_init_char_ptr_error_on_char_ptr_is_malformed),
            cmocka_unit_test(check_init_char_ptr),
            cmocka_unit_test(check_init_uintmax_t_error_on_object_is_null),
            cmocka_unit_test(check_init_uintmax_t),
            cmocka_unit_test(check_init_intmax_t_error_on_object_is_null),
            cmocka_unit_test(check_init_intmax_t),
            cmocka_unit_test(check_init_integer_error_on_object_is_null),
            cmocka_unit_test(check_init_integer_error_on_other_is_null),
            cmocka_unit_test(check_init_integer),
            cmocka_unit_test(check_init_error_on_object_is_null),
            cmocka_unit_test(check_init),
            cmocka_unit_test(check_set_char_ptr_error_on_object_is_null),
            cmocka_unit_test(check_set_char_ptr_error_on_char_ptr_is_null),
            cmocka_unit_test(check_set_char_ptr_error_on_char_ptr_is_malformed),
            cmocka_unit_test(check_set_char_ptr),
            cmocka_unit_test(check_set_uintmax_t_error_on_object_is_null),
            cmocka_unit_test(check_set_uintmax_t),
            cmocka_unit_test(check_set_intmax_t_error_on_object_is_null),
            cmocka_unit_test(check_set_intmax_t),
            cmocka_unit_test(check_set_integer_error_on_object_is_null),
            cmocka_unit_test(check_set_integer_error_on_other_is_null),
            cmocka_unit_test(check_set_integer),
            cmocka_unit_test(check_add_error_on_object_is_null),
            cmocka_unit_test(check_add_error_on_other_is_null),
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_uintmax_t_error_on_object_is_null),
            cmocka_unit_test(check_add_uintmax_t),
            cmocka_unit_test(check_subtract_error_on_object_is_null),
            cmocka_unit_test(check_subtract_error_on_other_is_null),
            cmocka_unit_test(check_subtract),
            cmocka_unit_test(check_subtract_uintmax_t_error_on_object_is_null),
            cmocka_unit_test(check_subtract_uintmax_t),
            cmocka_unit_test(check_divide_error_on_object_is_null),
            cmocka_unit_test(check_divide_error_on_divisor_is_null),
            cmocka_unit_test(check_divide_error_on_divide_by_zero),
            cmocka_unit_test(check_divide),
            cmocka_unit_test(check_multiply_error_on_object_is_null),
            cmocka_unit_test(check_multiply_error_on_other_is_null),
            cmocka_unit_test(check_multiply),
            cmocka_unit_test(check_absolute_error_on_object_is_null),
            cmocka_unit_test(check_absolute),
            cmocka_unit_test(check_negate_error_on_object_is_null),
            cmocka_unit_test(check_negate),
            cmocka_unit_test(check_compare),
            cmocka_unit_test(check_hash),
            cmocka_unit_test(check_and_error_on_object_is_null),
            cmocka_unit_test(check_and_error_on_other_is_null),
            cmocka_unit_test(check_and),
            cmocka_unit_test(check_or_error_on_object_is_null),
            cmocka_unit_test(check_or_error_on_other_is_null),
            cmocka_unit_test(check_or),
            cmocka_unit_test(check_not_error_on_object_is_null),
            cmocka_unit_test(check_not),
            cmocka_unit_test(check_xor_error_on_object_is_null),
            cmocka_unit_test(check_xor_error_on_other_is_null),
            cmocka_unit_test(check_xor),
            cmocka_unit_test(check_shift_left_error_on_object_is_null),
            cmocka_unit_test(check_shift_left),
            cmocka_unit_test(check_shift_right_error_on_object_is_null),
            cmocka_unit_test(check_shift_right),
            cmocka_unit_test(check_length_error_on_object_is_null),
            cmocka_unit_test(check_length_error_on_out_is_null),
            cmocka_unit_test(check_length),
            cmocka_unit_test(check_count_error_on_object_is_null),
            cmocka_unit_test(check_count_error_on_out_is_null),
            cmocka_unit_test(check_count),
            cmocka_unit_test(check_get_error_on_object_is_null),
            cmocka_unit_test(check_get_error_on_out_is_null),
            cmocka_unit_test(check_get),
            cmocka_unit_test(check_set_error_on_object_is_null),
            cmocka_unit_test(check_set),
            cmocka_unit_test(check_find_error_on_object_is_null),
            cmocka_unit_test(check_find_error_on_out_is_null),
            cmocka_unit_test(check_find_error_on_needle_not_found),
            cmocka_unit_test(check_find),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
