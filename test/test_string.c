#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <sea-turtle.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_invalidate(NULL));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object = {};
    assert_true(sea_turtle_string_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_init(NULL,
                                        (void*)1,
                                        1,
                                        (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_error_on_char_ptr_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_init((void *)1,
                                        NULL,
                                        1,
                                        (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_NULL,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_error_on_size_is_zero(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_init((void *)1,
                                        (void *)1,
                                        0,
                                        (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_SIZE_IS_ZERO, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_init((void *)1,
                                        (void *)1,
                                        1,
                                        NULL));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_error_on_empty_char_sequence(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const char input[] = u8"";
    struct sea_turtle_string object;
    size_t out;
    assert_false(sea_turtle_string_init(&object,
                                       input,
                                       sizeof(input),
                                       &out));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_EMPTY_CHAR_SEQUENCE,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_error_on_char_ptr_is_malformed(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const char input0[] = {(char)0xC0, (char)0x80};
    struct sea_turtle_string object;
    size_t out;
    assert_false(sea_turtle_string_init(&object,
                                       input0,
                                       sizeof(input0),
                                       &out));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const char input1[] = {(char)0x2F, (char)0xC0, (char)0xAE,
                           (char)0x2E, (char)0x2F};
    assert_false(sea_turtle_string_init(&object,
                                       input1,
                                       sizeof(input1),
                                       &out));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const char input2[] = {(char)0xC1, (char)0x81};
    assert_false(sea_turtle_string_init(&object,
                                       input2,
                                       sizeof(input2),
                                       &out));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_error_on_memory_allocation_failed(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object;
    size_t out;
    const char chars[] = u8"hold my beer!🍺";
    malloc_is_overridden = true;
    assert_false(sea_turtle_string_init(&object,
                                        chars,
                                        sizeof(chars),
                                        &out));
    malloc_is_overridden = false;
    assert_int_equal(SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object;
    size_t out;
    const char chars[] = u8"hello world!👋";
    assert_true(sea_turtle_string_init(&object,
                                       chars,
                                       sizeof(chars),
                                       &out));
    assert_non_null(object.data);
    assert_memory_equal(object.data, chars, sizeof(chars));
    assert_int_equal(object.size, sizeof(chars));
    assert_int_equal(object.count, 13);
    assert_true(sea_turtle_string_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_string_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_init_string(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_string_error_no_other_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_init_string((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OTHER_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_init_string(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const char chars[] = u8"turtle 🐢!";
    struct sea_turtle_string other;
    size_t out;
    assert_true(sea_turtle_string_init(&other, chars, sizeof(chars), &out));
    struct sea_turtle_string object;
    assert_true(sea_turtle_string_init_string(&object, &other));
    assert_ptr_not_equal(other.data, object.data);
    assert_memory_equal(other.data, object.data, other.size);
    assert_int_equal(other.size, object.size);
    assert_int_equal(other.count, object.count);
    assert_int_equal(other.hash, object.hash);
    assert_true(sea_turtle_string_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&other));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_count(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_count((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_count(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object;
    const char chars[] = u8" ";
    size_t out;
    assert_true(sea_turtle_string_init(&object,
                                       chars,
                                       sizeof(chars),
                                       &out));
    assert_int_equal(object.count, 1);
    assert_true(sea_turtle_string_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_compare(void **state) {
    size_t out;
    struct sea_turtle_string i;
    assert_true(sea_turtle_string_init(&i, u8"a", sizeof(u8"a"), &out));
    struct sea_turtle_string o;
    assert_true(sea_turtle_string_init(&o, u8"b", sizeof(u8"b"), &out));

    assert_int_equal((-1), sea_turtle_string_compare(&i, &o));
    assert_int_equal((-1), sea_turtle_string_compare(&i, NULL));
    assert_int_equal((-1), sea_turtle_string_compare(&o, NULL));
    assert_int_equal(0, sea_turtle_string_compare(&i, &i));
    assert_int_equal(0, sea_turtle_string_compare(&o, &o));
    assert_int_equal(1, sea_turtle_string_compare(&o, &i));
    assert_int_equal(1, sea_turtle_string_compare(NULL, &i));
    assert_int_equal(1, sea_turtle_string_compare(NULL, &o));

    assert_true(sea_turtle_string_invalidate(&o));
    assert_true(sea_turtle_string_invalidate(&i));

    abort_is_overridden = true;
    expect_function_call(cmocka_test_abort);
    sea_turtle_string_compare(NULL, NULL);
    abort_is_overridden = false;
}

static void check_hash(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object;
    const char chars[] = u8"🦖 t-rex";
    size_t out;
    assert_true(sea_turtle_string_init(&object, chars, sizeof(chars), &out));
    assert_int_not_equal(object.hash, 0);
    assert_true(sea_turtle_string_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_first(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_first((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_first(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object;
    size_t out;
    const char input0[] = u8"🙃";
    assert_true(sea_turtle_string_init(&object,
                                       input0,
                                       sizeof(input0),
                                       &out));
    const uint8_t *at;
    assert_true(sea_turtle_string_first(&object, &at));
    assert_ptr_equal(object.data, at);
    assert_true(sea_turtle_string_invalidate(&object));
    const char input1[] = u8"hello";
    assert_true(sea_turtle_string_init(&object,
                                       input1,
                                       sizeof(input1),
                                       &out));
    assert_true(sea_turtle_string_first(&object, &at));
    assert_ptr_equal(object.data, at);
    assert_true(sea_turtle_string_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_last(NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_last((void *)1, NULL));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_last(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object;
    size_t out;
    const char input0[] = u8"🖖";
    assert_true(sea_turtle_string_init(&object,
                                       input0,
                                       sizeof(input0),
                                       &out));
    const uint8_t *at;
    assert_true(sea_turtle_string_last(&object, &at));
    assert_ptr_equal(object.data, at);
    assert_true(sea_turtle_string_invalidate(&object));
    const char input1[] = u8"world";
    assert_true(sea_turtle_string_init(&object,
                                       input1,
                                       sizeof(input1),
                                       &out));
    assert_true(sea_turtle_string_last(&object, &at));
    assert_ptr_equal(object.data + out - 1, at);
    assert_true(sea_turtle_string_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_next_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_next(NULL, (void *)1, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_next_error_on_at_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_next((void *)1, NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_AT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_next_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_next((void *)1, (void *)1, NULL));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_next_error_on_at_is_out_of_bounds(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const uint8_t chars[] = {0x00};
    struct sea_turtle_string object = {
            .data = (uint8_t*) &chars,
            .size = 1
    };
    const uint8_t *at = &chars[object.size];
    assert_false(sea_turtle_string_next(&object, at, &at));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_next_error_on_at_is_invalid(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const uint8_t chars[] = {0x80, 0x00};
    struct sea_turtle_string object = {
            .data = (uint8_t*) &chars,
            .size = 1
    };
    const uint8_t *at = &chars[0];
    assert_false(sea_turtle_string_next(&object, at, &at));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_AT_IS_INVALID, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_next_error_on_end_of_sequence(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const uint8_t chars[] = {0x43, 0x00};
    struct sea_turtle_string object = {
            .data = (uint8_t*) &chars,
            .size = 1
    };
    const uint8_t *at = &chars[0];
    assert_false(sea_turtle_string_next(&object, at, &at));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_next(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object;
    size_t out;
    const char input[] = u8"_😇=";
    assert_true(sea_turtle_string_init(&object,
                                       input,
                                       sizeof(input),
                                       &out));
    const uint8_t *at;
    assert_true(sea_turtle_string_first(&object, &at));
    assert_ptr_equal(object.data, at);
    assert_int_equal('_', *at);
    assert_true(sea_turtle_string_next(&object, at, &at));
    assert_ptr_equal(object.data + 1, at);
    assert_true(sea_turtle_string_next(&object, at, &at));
    assert_int_equal('=', *at);
    assert_false(sea_turtle_string_next(&object, at, &at));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE, sea_turtle_error);
    assert_true(sea_turtle_string_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_prev_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_prev(NULL, (void *)1, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_prev_error_on_at_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_prev((void *)1, NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_AT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_prev_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_prev((void *)1, (void *)1, NULL));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_prev_error_on_at_is_out_of_bounds(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const uint8_t chars[] = {0x00};
    struct sea_turtle_string object = {
            .data = (uint8_t*) &chars,
            .size = 1
    };
    const uint8_t *at = &chars[object.size];
    assert_false(sea_turtle_string_prev(&object, at, &at));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_prev_error_on_at_is_invalid(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const uint8_t chars[] = {0x80, 0x00};
    struct sea_turtle_string object = {
            .data = (uint8_t*) &chars,
            .size = 1
    };
    const uint8_t *at = &chars[0];
    assert_false(sea_turtle_string_prev(&object, at, &at));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_AT_IS_INVALID, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_prev_error_on_end_of_sequence(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const uint8_t chars[] = {0x43, 0x00};
    struct sea_turtle_string object = {
            .data = (uint8_t*) &chars,
            .size = 1
    };
    const uint8_t *at = &chars[0];
    assert_false(sea_turtle_string_prev(&object, at, &at));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_prev(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object;
    size_t out;
    const char input[] = u8"_😇=";
    assert_true(sea_turtle_string_init(&object,
                                       input,
                                       sizeof(input),
                                       &out));
    const uint8_t *at;
    assert_true(sea_turtle_string_last(&object, &at));
    assert_int_equal('=', *at);
    assert_true(sea_turtle_string_prev(&object, at, &at));
    assert_ptr_equal(object.data + 1, at);
    assert_true(sea_turtle_string_prev(&object, at, &at));
    assert_int_equal('_', *at);
    assert_false(sea_turtle_string_prev(&object, at, &at));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE, sea_turtle_error);
    assert_true(sea_turtle_string_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_code_point_error_on_object_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_code_point(NULL, (void *)1, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_code_point_error_on_at_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_code_point((void *)1, NULL, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_AT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_code_point_error_on_out_is_null(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    assert_false(sea_turtle_string_code_point((void *)1, (void *)1, NULL));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_OUT_IS_NULL, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_code_point_error_on_at_is_out_of_bounds(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const uint8_t chars[] = {0x00};
    struct sea_turtle_string object = {
            .data = (uint8_t*) &chars,
            .size = 1
    };
    const uint8_t *at = &chars[object.size];
    assert_false(sea_turtle_string_code_point(&object, at, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS,
                     sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_code_point_error_on_at_is_invalid(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    const uint8_t chars[] = {0x80, 0x00};
    struct sea_turtle_string object = {
            .data = (uint8_t*) &chars,
            .size = 1
    };
    const uint8_t *at = &chars[0];
    assert_false(sea_turtle_string_code_point(&object, at, (void *)1));
    assert_int_equal(SEA_TURTLE_STRING_ERROR_AT_IS_INVALID, sea_turtle_error);
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

static void check_code_point(void **state) {
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
    struct sea_turtle_string object;
    size_t out;
    const char chars[] = u8"$£ह€한🐉";
    assert_true(sea_turtle_string_init(&object,
                                       chars,
                                       sizeof(chars),
                                       &out));
    const uint8_t* at;
    assert_true(sea_turtle_string_first(&object, &at));
    uint32_t code_point;
    assert_true(sea_turtle_string_code_point(&object, at, &code_point));
    assert_int_equal(code_point, 0x24);
    assert_true(sea_turtle_string_next(&object, at, &at));
    assert_true(sea_turtle_string_code_point(&object, at, &code_point));
    assert_int_equal(code_point, 0xA3);
    assert_true(sea_turtle_string_next(&object, at, &at));
    assert_true(sea_turtle_string_code_point(&object, at, &code_point));
    assert_int_equal(code_point, 0x939);
    assert_true(sea_turtle_string_next(&object, at, &at));
    assert_true(sea_turtle_string_code_point(&object, at, &code_point));
    assert_int_equal(code_point, 0x20AC);
    assert_true(sea_turtle_string_next(&object, at, &at));
    assert_true(sea_turtle_string_code_point(&object, at, &code_point));
    assert_int_equal(code_point, 0xD55C);
    assert_true(sea_turtle_string_next(&object, at, &at));
    assert_true(sea_turtle_string_code_point(&object, at, &code_point));
    assert_int_equal(code_point, 0x1F409);
    assert_true(sea_turtle_string_invalidate(&object));
    sea_turtle_error = SEA_TURTLE_ERROR_NONE;
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_invalidate_error_on_object_is_null),
            cmocka_unit_test(check_invalidate),
            cmocka_unit_test(check_init_error_on_object_is_null),
            cmocka_unit_test(check_init_error_on_char_ptr_is_null),
            cmocka_unit_test(check_init_error_on_size_is_zero),
            cmocka_unit_test(check_init_error_on_out_is_null),
            cmocka_unit_test(check_init_error_on_empty_char_sequence),
            cmocka_unit_test(check_init_error_on_char_ptr_is_malformed),
            cmocka_unit_test(check_init_error_on_memory_allocation_failed),
            cmocka_unit_test(check_init),
            cmocka_unit_test(check_init_string_error_on_object_is_null),
            cmocka_unit_test(check_init_string_error_no_other_is_null),
            cmocka_unit_test(check_init_string),
            cmocka_unit_test(check_count_error_on_object_is_null),
            cmocka_unit_test(check_count_error_on_out_is_null),
            cmocka_unit_test(check_count),
            cmocka_unit_test(check_compare),
            cmocka_unit_test(check_hash),
            cmocka_unit_test(check_first_error_on_object_is_null),
            cmocka_unit_test(check_first_error_on_out_is_null),
            cmocka_unit_test(check_first),
            cmocka_unit_test(check_last_error_on_object_is_null),
            cmocka_unit_test(check_last_error_on_out_is_null),
            cmocka_unit_test(check_last),
            cmocka_unit_test(check_next_error_on_object_is_null),
            cmocka_unit_test(check_next_error_on_at_is_null),
            cmocka_unit_test(check_next_error_on_out_is_null),
            cmocka_unit_test(check_next_error_on_at_is_out_of_bounds),
            cmocka_unit_test(check_next_error_on_at_is_invalid),
            cmocka_unit_test(check_next_error_on_end_of_sequence),
            cmocka_unit_test(check_next),
            cmocka_unit_test(check_prev_error_on_object_is_null),
            cmocka_unit_test(check_prev_error_on_at_is_null),
            cmocka_unit_test(check_prev_error_on_out_is_null),
            cmocka_unit_test(check_prev_error_on_at_is_out_of_bounds),
            cmocka_unit_test(check_prev_error_on_at_is_invalid),
            cmocka_unit_test(check_prev_error_on_end_of_sequence),
            cmocka_unit_test(check_prev),
            cmocka_unit_test(check_code_point_error_on_object_is_null),
            cmocka_unit_test(check_code_point_error_on_at_is_null),
            cmocka_unit_test(check_code_point_error_on_out_is_null),
            cmocka_unit_test(check_code_point_error_on_at_is_out_of_bounds),
            cmocka_unit_test(check_code_point_error_on_at_is_invalid),
            cmocka_unit_test(check_code_point),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
