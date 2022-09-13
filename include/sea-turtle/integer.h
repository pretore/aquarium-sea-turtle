#ifndef _SEA_TURTLE_INTEGER_H_
#define _SEA_TURTLE_INTEGER_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <gmp.h>

#define SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL                     1
#define SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL                   2
#define SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED              3
#define SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL                        4
#define SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL                      5
#define SEA_TURTLE_INTEGER_ERROR_DIVISOR_IS_NULL                    6
#define SEA_TURTLE_INTEGER_ERROR_DIVISION_BY_ZERO                   7
#define SEA_TURTLE_INTEGER_ERROR_NEEDLE_NOT_FOUND                   8

struct sea_turtle_integer {
    mpz_t mpz;
};

struct sea_turtle_integer_range {
    uintmax_t first;
    uintmax_t last;
};

/**
 * @brief Initialize integer from char pointer.
 * <p>The char pointer's contents must be in one of the following formats:
 * <ul>
 * <li>hexadecimal number starts with <b>0x</b></li>
 * <li>binary number starts with <b>0b</b></li>
 * <li>octal number starts with <b>0</b></li>
 * <li>decimal otherwise</li>
 * </ul>
 * </p>
 * @param [in] object instance to be initialized.
 * @param [in] char_ptr number in one of the supported formats.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL if char_ptr is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED if char_ptr is not in
 * one of the recognised formats.
 */
bool sea_turtle_integer_init_with_char_ptr(struct sea_turtle_integer *object,
                                           const char *char_ptr);

/**
 * @brief Initialize integer from uintmax_t.
 * @param [in] object instance to be initialized.
 * @param [in] value number that the integer should contain initially.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_init_with_uintmax_t(struct sea_turtle_integer *object,
                                            uintptr_t value);

/**
 * @brief Initialize integer from intmax_t.
 * @param [in] object instance to be initialized.
 * @param [in] value number that the integer should contain initially.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_init_with_intmax_t(struct sea_turtle_integer *object,
                                           intmax_t value);

/**
 * @brief Initialize integer from other integer.
 * @param [in] object instance to be initialized.
 * @param [in] other integer whose value we will copy.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL if other is <i>NULL</i>.
 */
bool sea_turtle_integer_init_with_integer(
        struct sea_turtle_integer *restrict object,
        const struct sea_turtle_integer *restrict other);

/**
 * @brief Initialize integer.
 * @param [in] object instance to be initialized.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_init(struct sea_turtle_integer *object);

/**
 * @brief Invalidate integer.
 * <p>The actual <u>integer instance is not deallocated</u> since it may have
 * been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_invalidate(struct sea_turtle_integer *object);

/**
 * @brief Set the integer from char pointer.
 * <p>The char pointer's contents must be in one of the following formats:
 * <ul>
 * <li>hexadecimal number starts with <b>0x</b></li>
 * <li>binary number starts with <b>0b</b></li>
 * <li>octal number starts with <b>0</b></li>
 * <li>decimal otherwise</li>
 * </ul>
 * </p>
 * @param [in] object instance to be set.
 * @param [in] char_ptr number in one of the supported formats.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_NULL if char_ptr is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_CHAR_PTR_IS_MALFORMED if char_ptr is not in
 * one of the recognised formats.
 */
bool sea_turtle_integer_set_with_char_ptr(struct sea_turtle_integer *object,
                                          const char *char_ptr);

/**
 * @brief Set the integer from uintmax_t.
 * @param [in] object instance to be set.
 * @param [in] value number that the integer should be set to.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_set_with_uintmax_t(struct sea_turtle_integer *object,
                                           uintmax_t value);

/**
 * @brief Set the integer from intmax_t.
 * @param [in] object instance to be set.
 * @param [in] value number that the integer should be set to.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_set_with_intmax_t(struct sea_turtle_integer *object,
                                         intmax_t value);

/**
 * @brief Add two integers together.
 * @param [in,out] object add other to this integer.
 * @param [in] other integer instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL if other is <i>NULL</i>.
 */
bool sea_turtle_integer_add(struct sea_turtle_integer *object,
                            const struct sea_turtle_integer *other);

/**
 * @brief Subtract other integer from object.
 * @param [in,out] object integer from which other will be subtracted.
 * @param [in] other integer instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL if other is <i>NULL</i>.
 */
bool sea_turtle_integer_subtract(struct sea_turtle_integer *object,
                                 const struct sea_turtle_integer *other);

/**
 * @brief Divide integer by divisor.
 * @param [in,out] object integer which is to be divided.
 * @param [in] divisor integer instance.
 * @param [out] remainder receive remainder if provided.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_DIVISOR_IS_NULL if divisor is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_DIVISION_BY_ZERO if divisor is zero.
 */
bool sea_turtle_integer_divide(struct sea_turtle_integer *object,
                               const struct sea_turtle_integer *divisor,
                               struct sea_turtle_integer *remainder);

/**
 * @brief Multiply integer.
 * @param [in,out] object integer instance.
 * @param [in] other integer instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL if other is <i>NULL</i>.
 */
bool sea_turtle_integer_multiply(struct sea_turtle_integer *object,
                                 const struct sea_turtle_integer *other);

/**
 * @brief Retrieve absolute value.
 * @param [in,out] object integer instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_absolute(struct sea_turtle_integer *object);

/**
 * @brief Negate integer.
 * @param [in,out] object integer instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_negate(struct sea_turtle_integer *object);

/**
 * @brief Comparison function for integer.
 * @param [in] object integer instance.
 * @param [in] other integer instance.
 * @return <i>-1</i> if <b>object</b> is <u>less than</u> <b>other</b>,
 * <i>0</i> if <b>object</b> is <u>equal to</u> <b>other</b> or <i>1</i> if
 * <b>object</b> is <u>greater than</u> <b>other</b>.
 * @note If <b>object</b> and <b>other</b> is <i>NULL</i> then abort(3) is
 * called.
 */
int sea_turtle_integer_compare(const struct sea_turtle_integer *object,
                               const struct sea_turtle_integer *other);

/**
 * @brief Perform bitwise AND.
 * @param [in,out] object integer instance.
 * @param [in] other integer instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL if other is <i>NULL</i>.
 */
bool sea_turtle_integer_and(struct sea_turtle_integer *object,
                            const struct sea_turtle_integer *other);

/**
 * @brief Perform bitwise OR.
 * @param [in,out] object integer instance.
 * @param [in] other integer instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL if other is <i>NULL</i>.
 */
bool sea_turtle_integer_or(struct sea_turtle_integer *object,
                           const struct sea_turtle_integer *other);

/**
 * @brief Perform bitwise NOT.
 * @param [in,out] object integer instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_not(struct sea_turtle_integer *object);

/**
 * @brief Perform bitwise XOR.
 * @param [in,out] object integer instance.
 * @param [in] other integer instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OTHER_IS_NULL if other is <i>NULL</i>.
 */
bool sea_turtle_integer_xor(struct sea_turtle_integer *object,
                            const struct sea_turtle_integer *other);

/**
 * @brief Bitwise shift left the integer by given number of bits.
 * @param [in,out] object integer instance.
 * @param [in] nbits number of bits to left shift integer by.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_shift_left(struct sea_turtle_integer *object,
                                   uintmax_t nbits);

/**
 * @brief Bitwise shift right the integer by given number of bits.
 * @param [in,out] object integer instance.
 * @param [in] nbits number of bits to right shift integer by.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool sea_turtle_integer_shift_right(struct sea_turtle_integer *object,
                                    uintmax_t nbits);

/**
 * @brief Return the number of bits used for the value of integer (ignoring
 * the sign bit).
 * @param [in] object integer instance.
 * @param [out] out number of bits used to represent the value of the integer
 * (ignoring the sign bit).
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool sea_turtle_integer_length(const struct sea_turtle_integer *object,
                               uintmax_t *out);

/**
 * @brief Return the number of 1 bits for the value of integer (ignoring
 * the sign bit).
 * @param [in] object integer instance.
 * @param [out] out number of 1 bits in the value of integer (ignoring the
 * sign bit).
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool sea_turtle_integer_count(const struct sea_turtle_integer *object,
                              uintmax_t *out);

/**
 * @brief Return the bit at the given index for the two's complement
 * representation of integer.
 * @param [in] object integer instance.
 * @param [in] at index of bit to retrieve where the least significant bit is 0.
 * @param [out] out receive bit at the given index.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @see <a href=https://en.wikipedia.org/wiki/Two%27s_complement> two's
 * complement</a>
 */
bool sea_turtle_integer_get(const struct sea_turtle_integer *object,
                            uintmax_t at,
                            bool *out);

/**
 * @brief Set the bit at the given index for the two's complement
 * representation of integer.
 * @param [in] object integer instance.
 * @param [in] at index of bit to set where the least significant bit is 0.
 * @param [in] value set the bit to value at the given index.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @see <a href=https://en.wikipedia.org/wiki/Two%27s_complement> two's
 * complement</a>
 */
bool sea_turtle_integer_set(struct sea_turtle_integer *object,
                            uintmax_t at,
                            bool value);

/**
 * @brief Find the bit in the integer.
 * @param [in] object integer instance.
 * @param [in] values if provided, will limit the search to only between the
 * given indexes inclusively.
 * @param [in] needle bit that we are looking for.
 * @param [out] out receive the index of the bit found in the integer where
 * the least significant bit is 0.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_INTEGER_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEA_TURTLE_INTEGER_ERROR_NEEDLE_NOT_FOUND if needle was not found
 * in the integer.
 */
bool sea_turtle_integer_find(const struct sea_turtle_integer *object,
                             const struct sea_turtle_integer_range *values,
                             bool needle,
                             uintmax_t *out);

#endif /* _SEA_TURTLE_INTEGER_H_ */
