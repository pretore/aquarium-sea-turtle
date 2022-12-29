#ifndef _SEA_TURTLE_PRIVATE_STRING_H_
#define _SEA_TURTLE_PRIVATE_STRING_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <sea-turtle.h>

/**
 * @brief Check if char sequence contains a valid UTF-8 sequence.
 * @param [in] char_ptr pointer to char sequence.
 * @param [in] size number of chars in the char sequence.
 * @param [out] out receive number of chars processed in the sequence until
 * <b>size</b> chars processed or <i>NULL</i> encountered.
 * @param [out] count optionally receive the count of code points in the UTF-8
 * sequence.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_NULL if char_ptr is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_SIZE_IS_ZERO is size is zero.
 * @throws SEA_TURTLE_STRING_ERROR_CHAR_PTR_IS_MALFORMED if char_ptr does not
 * refer to a valid UTF-8 sequence.
 */
bool sea_turtle_string_is_utf8_sequence(const char *char_ptr,
                                        size_t size,
                                        size_t *out,
                                        uintmax_t *count);

/**
 * @brief Set the size of the backing buffer.
 * <p>Resizing the backing buffer while ensuring that it is <i>NULL</i>
 * terminated.</p>
 * @param [in] object string instance.
 * @param [in] size desired size of backing buffer including <i>NULL</i>
 * terminator.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEA_TURTLE_STRING_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED if memory
 * allocation failed while adjusting backing buffer.
 */
bool sea_turtle_string_set_size(struct sea_turtle_string *object,
                                size_t size);

#endif /* _SEA_TURTLE_PRIVATE_STRING_H_ */
