#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <time.h>
#include <sea-turtle.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_invalidate(NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_char_ptr_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_init_char_ptr(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_char_ptr_error_on_char_ptr_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_init_char_ptr((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void
check_init_char_ptr_error_on_char_ptr_is_malformed(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_false(sea_turtle_integer_init_char_ptr(
            &object, "28761236187720391aa"));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_char_ptr(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_true(sea_turtle_integer_init_char_ptr(
            &object,
            "826221238914710294871294812617285631892198412643162192184281736249"
            "634961294639146710643197329057023197493217781236481246031640871753"
            "298171906431023762174693164013471937498357293653296589726387162386"
            "128736781263012746398610461309483691386490123649817259873297592837"
            "932657821568732123423425427617843198352371433532824595485248132"));
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_uintmax_t_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_init_uintmax_t(NULL, 0));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_uintmax_t(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&object, 8972));
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_intmax_t_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_init_intmax_t(NULL, 2134));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_intmax_t(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_true(sea_turtle_integer_init_intmax_t(&object, -2321));
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_integer_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_init_integer(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_integer_error_on_other_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_init_integer((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_integer(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 98123));
    struct sea_turtle_integer o = {};
    assert_true(sea_turtle_integer_init_integer(&o, &i));
    assert_int_equal(mpz_get_ui(o.mpz), 98123);
    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_init(NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_true(sea_turtle_integer_init(&object));
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_set_char_ptr_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_set_char_ptr(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_set_char_ptr_error_on_char_ptr_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_set_char_ptr((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void
check_set_char_ptr_error_on_char_ptr_is_malformed(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_true(sea_turtle_integer_init(&object));
    assert_false(sea_turtle_integer_set_char_ptr(
            &object, "28761236187720391aa"));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED,
                     sea_turtle_error);
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_set_char_ptr(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_true(sea_turtle_integer_init(&object));
    assert_true(sea_turtle_integer_set_char_ptr(
            &object,
            "826221238914710294871294812617285631892198412643162192184281736249"
            "634961294639146710643197329057023197493217781236481246031640871753"
            "298171906431023762174693164013471937498357293653296589726387162386"
            "128736781263012746398610461309483691386490123649817259873297592837"
            "932657821568732123423425427617843198352371433532824595485248132"));
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_set_uintmax_t_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_set_uintmax_t(NULL, 0));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_set_uintmax_t(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_true(sea_turtle_integer_init(&object));
    assert_true(sea_turtle_integer_set_uintmax_t(&object, 8972));
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_set_intmax_t_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_set_intmax_t(NULL, 2134));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_set_intmax_t(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object = {};
    assert_true(sea_turtle_integer_init(&object));
    assert_true(sea_turtle_integer_set_intmax_t(&object, -2321));
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_add(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_add_error_on_other_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_add((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_add(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 72163));
    struct sea_turtle_integer o = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&o, 21786));
    assert_true(sea_turtle_integer_add(&i, &o));
    assert_int_equal(mpz_get_si(i.mpz), 93949);
    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_add_uintmax_t_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_add_uintmax_t(NULL, 72163));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_add_uintmax_t(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 72163));
    assert_true(sea_turtle_integer_add_uintmax_t(&i, 21786));
    assert_int_equal(mpz_get_si(i.mpz), 93949);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_subtract_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_subtract(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_subtract_error_on_other_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_subtract((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_subtract(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 72163));
    struct sea_turtle_integer o = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&o, 21786));
    assert_true(sea_turtle_integer_subtract(&i, &o));
    assert_int_equal(mpz_get_si(i.mpz), 50377);
    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_subtract_uintmax_t_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_subtract_uintmax_t(NULL, 21786));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_subtract_uintmax_t(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 72163));
    assert_true(sea_turtle_integer_subtract_uintmax_t(&i, 21786));
    assert_int_equal(mpz_get_si(i.mpz), 50377);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_divide_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_divide(NULL, (void *)1, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_divide_error_on_divisor_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_divide((void *)1, NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_DIVISOR_IS_NULL,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_divide_error_on_divide_by_zero(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 1000));
    struct sea_turtle_integer o = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&o, 0));
    assert_false(sea_turtle_integer_divide(&i, &o, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_DIVISION_BY_ZERO,
                     sea_turtle_error);
    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_divide(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 1000));
    struct sea_turtle_integer o = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&o, 4));
    assert_true(sea_turtle_integer_divide(&i, &o, NULL));
    assert_int_equal(mpz_get_si(i.mpz), 250);
    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 1000));
    assert_true(sea_turtle_integer_init_uintmax_t(&o, 3));
    struct sea_turtle_integer p = {};
    assert_true(sea_turtle_integer_init(&p));
    assert_true(sea_turtle_integer_divide(&i, &o, &p));
    assert_int_equal(mpz_get_si(i.mpz), 333);
    assert_int_equal(mpz_get_si(p.mpz), 1);
    assert_true(sea_turtle_integer_invalidate(&p));
    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_multiply_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_multiply(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_multiply_error_on_other_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_multiply((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_multiply(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 10));
    struct sea_turtle_integer o = {};
    assert_true(sea_turtle_integer_init_intmax_t(&o, -10));
    assert_true(sea_turtle_integer_multiply(&i, &o));
    assert_int_equal(mpz_get_si(i.mpz), -100);
    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_absolute_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_absolute(NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_absolute(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_intmax_t(&i, -1));
    assert_int_equal(mpz_get_si(i.mpz), -1);
    assert_true(sea_turtle_integer_absolute(&i));
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_true(sea_turtle_integer_absolute(&i));
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_negate_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_negate(NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_negate(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_intmax_t(&i, -1));
    assert_int_equal(mpz_get_si(i.mpz), -1);
    assert_true(sea_turtle_integer_negate(&i));
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_true(sea_turtle_integer_negate(&i));
    assert_int_equal(mpz_get_si(i.mpz), -1);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_compare(void **state) {
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init(&i));
    struct sea_turtle_integer o;
    assert_true(sea_turtle_integer_init_uintmax_t(&o, 1));

    assert_int_equal((-1), sea_turtle_integer_compare(&i, &o));
    assert_int_equal((-1), sea_turtle_integer_compare(&i, NULL));
    assert_int_equal((-1), sea_turtle_integer_compare(&o, NULL));
    assert_int_equal(0, sea_turtle_integer_compare(&i, &i));
    assert_int_equal(0, sea_turtle_integer_compare(&o, &o));
    assert_int_equal(1, sea_turtle_integer_compare(&o, &i));
    assert_int_equal(1, sea_turtle_integer_compare(NULL, &i));
    assert_int_equal(1, sea_turtle_integer_compare(NULL, &o));

    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));

    abort_is_overridden = true;
    expect_function_call(cmocka_test_abort);
    sea_turtle_integer_compare(NULL, NULL);
    abort_is_overridden = false;
}

static void check_hash(void **state) {
    srand(time(NULL));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer object;
    assert_true(sea_turtle_integer_init_uintmax_t(
            &object, (1 + rand()) % (UINTMAX_MAX - 1)));
    uintmax_t code;
    assert_true(sea_turtle_integer_hash(&object, &code));
    assert_int_not_equal(code, 0);
    assert_true(sea_turtle_integer_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_and_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_and(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_and_error_on_other_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_and((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_and(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init(&i));
    struct sea_turtle_integer o = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&o, 1));

    assert_true(sea_turtle_integer_and(&o, &o));
    assert_int_equal(mpz_get_si(o.mpz), 1);
    assert_true(sea_turtle_integer_and(&i, &o));
    assert_int_equal(mpz_get_si(i.mpz), 0);
    assert_true(sea_turtle_integer_and(&o, &i));
    assert_int_equal(mpz_get_si(o.mpz), 0);
    assert_true(sea_turtle_integer_and(&i, &i));
    assert_int_equal(mpz_get_si(i.mpz), 0);

    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_or_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_or(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_or_error_on_other_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_or((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_or(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init(&i));
    struct sea_turtle_integer o = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&o, 1));

    assert_true(sea_turtle_integer_or(&o, &o));
    assert_int_equal(mpz_get_si(o.mpz), 1);
    assert_true(sea_turtle_integer_or(&o, &i));
    assert_int_equal(mpz_get_si(o.mpz), 1);
    assert_true(sea_turtle_integer_or(&i, &o));
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(sea_turtle_integer_init(&i));
    assert_true(sea_turtle_integer_or(&i, &i));
    assert_int_equal(mpz_get_si(i.mpz), 0);

    assert_true(sea_turtle_integer_invalidate(&o));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_not_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_not(NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_not(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 1));
    assert_true(sea_turtle_integer_not(&i));
    assert_int_equal(mpz_get_si(i.mpz), -2);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_xor_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_xor(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_xor_error_on_other_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_xor((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_xor(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init(&i));
    struct sea_turtle_integer o = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&o, 1));

    assert_true(sea_turtle_integer_xor(&i, &o));
    assert_int_equal(mpz_get_si(i.mpz), 1);
    assert_true(sea_turtle_integer_xor(&i, &o));
    assert_int_equal(mpz_get_si(i.mpz), 0);

    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(sea_turtle_integer_invalidate(&o));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_shift_left_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_shift_left(NULL, 0));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_shift_left(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 1));
    assert_int_equal(1, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_shift_left(&i, 10));
    assert_int_equal(1024, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(sea_turtle_integer_init_intmax_t(&i, -1));
    assert_int_equal(-1, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_shift_left(&i, 10));
    assert_int_equal(-1024, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_shift_right_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_shift_right(NULL, 0));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_shift_right(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 1024));
    assert_int_equal(1024, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_shift_right(&i, 10));
    assert_int_equal(1, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(sea_turtle_integer_init_intmax_t(&i, -1024));
    assert_int_equal(-1024, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_shift_right(&i, 10));
    assert_int_equal(-1, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_length_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_length(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_length_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_length((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_length(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 1024));
    assert_int_equal(1024, mpz_get_si(i.mpz));
    uintmax_t length;
    assert_true(sea_turtle_integer_length(&i, &length));
    assert_int_equal(11, length);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(sea_turtle_integer_init_intmax_t(&i, -2048));
    assert_int_equal(-2048, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_length(&i, &length));
    assert_int_equal(12, length);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_count(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_count((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_count(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 1024));
    assert_int_equal(1024, mpz_get_si(i.mpz));
    uintmax_t count;
    assert_true(sea_turtle_integer_count(&i, &count));
    assert_int_equal(1, count);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 255));
    assert_int_equal(255, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_count(&i, &count));
    assert_int_equal(8, count);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_get(NULL, 0, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_get((void *)1, 0, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_get(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init_uintmax_t(&i, 1025));
    bool value;
    assert_true(sea_turtle_integer_get(&i, 0, &value));
    assert_true(value);
    assert_true(sea_turtle_integer_get(&i, 1024, &value));
    assert_false(value);
    assert_true(sea_turtle_integer_get(&i, 10, &value));
    assert_true(value);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(sea_turtle_integer_init_uintmax_t(&i, -1025));
    assert_true(sea_turtle_integer_get(&i, 1024, &value));
    assert_false(value);
    /* twos compliment representation for a negative number */
    for (uintmax_t o = 0; o < 10; o++) {
        assert_true(sea_turtle_integer_get(&i, o, &value));
        assert_true(value);
    }
    assert_true(sea_turtle_integer_get(&i, 10, &value));
    assert_false(value);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_set_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_set(NULL, 0, false));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_set(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init(&i));
    assert_int_equal(0, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_set(&i, 10, true));
    bool value;
    assert_true(sea_turtle_integer_get(&i, 10, &value));
    assert_true(value);
    assert_true(sea_turtle_integer_set(&i, 0, true));
    assert_true(sea_turtle_integer_negate(&i));
    /* twos compliment representation for a negative number */
    assert_true(sea_turtle_integer_get(&i, 10, &value));
    assert_false(value);
    assert_true(sea_turtle_integer_negate(&i));
    assert_true(sea_turtle_integer_set(&i, 1024, false));
    assert_true(sea_turtle_integer_get(&i, 1024, &value));
    assert_false(value);
    assert_true(sea_turtle_integer_set(&i, 10, false));
    assert_true(sea_turtle_integer_get(&i, 10, &value));
    assert_false(value);
    assert_int_equal(1, mpz_get_si(i.mpz));
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_find_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_find(NULL, (void *)1, false, (void *)1));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_find_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_integer_find((void *)1, (void *)1, true, NULL));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_find_error_on_needle_not_found(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init(&i));
    uintmax_t at;
    assert_false(sea_turtle_integer_find(&i, NULL, true, &at));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_NEEDLE_NOT_FOUND,
                     sea_turtle_error);
    assert_true(sea_turtle_integer_set(&i, 212, true));
    struct sea_turtle_integer_range values = {
            .first = 19,
            .last = 100
    };
    assert_false(sea_turtle_integer_find(&i, &values, true, &at));
    assert_int_equal(SEA_TURTLE_INTEGER_ERROR_NEEDLE_NOT_FOUND,
                     sea_turtle_error);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_find(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_integer i = {};
    assert_true(sea_turtle_integer_init(&i));
    assert_true(sea_turtle_integer_set(&i, 1023, true));
    uintmax_t at;
    assert_true(sea_turtle_integer_find(&i, NULL, false, &at));
    assert_int_equal(0, at);
    assert_true(sea_turtle_integer_find(&i, NULL, true, &at));
    assert_int_equal(1023, at);
    assert_true(sea_turtle_integer_invalidate(&i));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
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
