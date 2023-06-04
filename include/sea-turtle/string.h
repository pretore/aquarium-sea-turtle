#ifndef _SEA_TURTLE_STRING_H_
#define _SEA_TURTLE_STRING_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <sea-urchin.h>

#define SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL \
    SEA_URCHIN_ERROR_OUT_IS_NULL
#define SEA_TURTLE_STRING_ERROR_OTHER_IS_NULL \
    SEA_URCHIN_ERROR_OTHER_IS_NULL
#define SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_NULL \
    SEA_URCHIN_ERROR_VALUE_IS_NULL
#define SEA_TURTLE_STRING_ERROR_OUT_IS_NULL \
    SEA_URCHIN_ERROR_OUT_IS_NULL
#define SEA_TURTLE_STRING_ERROR_SIZE_IS_ZERO \
    SEA_URCHIN_ERROR_VALUE_IS_ZERO
#define SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED \
    SEA_URCHIN_ERROR_VALUE_IS_INVALID
#define SEA_TURTLE_STRING_ERROR_STRING_IS_EMPTY \
    SEA_URCHIN_ERROR_IS_EMPTY
#define SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED \
    SEA_URCHIN_ERROR_MEMORY_ALLOCATION_FAILED
#define SEA_TURTLE_STRING_ERROR_AT_IS_NULL \
    SEA_URCHIN_ERROR_ITEM_IS_NULL
#define SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS \
    SEA_URCHIN_ERROR_ITEM_IS_OUT_OF_BOUNDS
#define SEA_TURTLE_STRING_ERROR_AT_IS_INVALID \
    SEA_URCHIN_ERROR_VALUE_IS_INVALID
#define SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE \
    SEA_URCHIN_ERROR_END_OF_SEQUENCE

struct sea_turtle_string {
    uint8_t *data;
    size_t size;
    uintmax_t count;
    uintmax_t hash;
};

/**
 * @brief Initialize string from other string.
 * @param [in] object instance to be initialized.
 * @param [in] other string whose value we will copy.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_OTHER_IS_NULL if other is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED if there is
 * insufficient memory to initialize the string instance.
 */
int sea_turtle_string_init_string(struct sea_turtle_string *object,
                                  const struct sea_turtle_string *other);

/**
 * @brief Initialize string with an UTF-8 sequence.
 * <p>The string instance will be initialized with the contents of the UTF-8
 * sequence up to the first <i>NULL</i> char occurrence or <b>size</b> chars
 * have been read.</p>
 * @param [in] object instance to be initialized.
 * @param [in] char_ptr UTF-8 sequence to read.
 * @param [in] size upper limit in the number of chars to read up to.
 * @param [out] out receive the number of chars we have read up to.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_NULL if char_ptr is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_SIZE_IS_ZERO is size is zero.
 * @throws SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED if char_ptr does not
 * refer to a valid UTF-8 sequence.
 * @throws SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED if there is
 * insufficient memory to initialize the string instance.
 */
int sea_turtle_string_init(struct sea_turtle_string *object,
                           const char *char_ptr,
                           size_t size,
                           size_t *out);

/**
 * @brief Invalidate string.
 * <p>The actual <u>string instance is not deallocated</u> since it may have
 * been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
int sea_turtle_string_invalidate(struct sea_turtle_string *object);

/**
 * @brief Receive the count of code points.
 * @param [in] object string instance.
 * @param [out] out receive the count of code points.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int sea_turtle_string_count(const struct sea_turtle_string *object,
                            uintmax_t *out);

/**
 * @brief Comparison function for string.
 * @param [in] object string instance.
 * @param [in] other string instance.
 * @return <i>-1</i> if <b>object</b> is <u>less than</u> <b>other</b>,
 * <i>0</i> if <b>object</b> is <u>equal to</u> <b>other</b> or <i>1</i> if
 * <b>object</b> is <u>greater than</u> <b>other</b>.
 * @note If <b>object</b> and <b>other</b> is <i>NULL</i> then abort(3) is
 * called.
 */
int sea_turtle_string_compare(const struct sea_turtle_string *object,
                              const struct sea_turtle_string *other);

/**
 * @brief Retrieve the hash code.
 * @param [in] object string instance.
 * @param [out] out receive the hash code.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int sea_turtle_string_hash(const struct sea_turtle_string *object,
                           uintmax_t *out);

/**
 * @brief Retrieve the first UTF-8 encoded symbol.
 * @param [in] object string instance.
 * @param [out] out receive the <u>address of</u> the first UTF-8 encoded
 * symbol.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_STRING_IS_EMPTY if string is empty.
 */
int sea_turtle_string_first(const struct sea_turtle_string *object,
                            const uint8_t **out);

/**
 * @brief Retrieve the last UTF-8 encoded symbol.
 * @param [in] object string instance.
 * @param [out] out receive the <u>address of</u> the last UTF-8 encoded
 * symbol.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_STRING_IS_EMPTY if string is empty.
 */
int sea_turtle_string_last(const struct sea_turtle_string *object,
                           const uint8_t **out);

/**
 * @brief Retrieve the next UTF-8 encoded symbol.
 * @param [in] object string instance.
 * @param [in] at current UTF-8 encoded symbol.
 * @param [out] out receive the <u>address of</u> the next UTF-8 encoded symbol.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_AT_IS_NULL if at is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS if at does not refer
 * to a UTF-8 encoded symbol contained within object.
 * @throws SEA_TURTLE_STRING_ERROR_AT_IS_INVALID if at does not refer to a
 * valid UTF-8 encoded symbol.
 * @throws SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE if there are no more UTF-8
 * encoded symbols.
 */
int sea_turtle_string_next(const struct sea_turtle_string *object,
                           const uint8_t *at,
                           const uint8_t **out);

/**
 * @brief Retrieve the previous UTF-8 encoded symbol.
 * @param [in] object string instance.
 * @param [in] at current UTF-8 encoded symbol.
 * @param [out] out receive the <u>address of</u> the previous UTF-8 encoded
 * symbol.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_AT_IS_NULL if at is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS if at does not refer
 * to a UTF-8 encoded symbol contained within object.
 * @throws SEA_TURTLE_STRING_ERROR_AT_IS_INVALID if at does not refer to a
 * valid UTF-8 encoded symbol.
 * @throws SEA_TURTLE_STRING_ERROR_END_OF_SEQUENCE if there are no more UTF-8
 * encoded symbols.
 */
int sea_turtle_string_prev(const struct sea_turtle_string *object,
                           const uint8_t *at,
                           const uint8_t **out);

/**
 * @brief Get code point from UTF-8 encoded symbol.
 * @param [in] object string instance.
 * @param [in] at UTF-8 encoded symbol.
 * @param [out] out receive the code point for the UTF-8 encoded symbol.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_AT_IS_NULL if at is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_AT_IS_OUT_OF_BOUNDS if at does not refer
 * to a UTF-8 encoded symbol contained within object.
 * @throws SEA_TURTLE_STRING_ERROR_AT_IS_INVALID if at does not refer to a
 * valid UTF-8 encoded symbol.
 */
int sea_turtle_string_code_point(const struct sea_turtle_string *object,
                                 const uint8_t *at,
                                 uint32_t *out);

#endif /* _SEA_TURTLE_STRING_H_ */
