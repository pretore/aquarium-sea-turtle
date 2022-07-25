#ifndef _SEA_TURTLE_ERROR_H_
#define _SEA_TURTLE_ERROR_H_

#include <stddef.h>
#include <threads.h>

#define SEA_TURTLE_ERROR_NONE                                 0

extern thread_local size_t sea_turtle_error;

#endif /* _SEA_TURTLE_ERROR_H_ */
