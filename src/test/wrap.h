#ifndef _SEA_TURTLE_TEST_WRAP_H_
#define _SEA_TURTLE_TEST_WRAP_H_

#ifdef TEST
#include <stdbool.h>

extern bool seagrass_required_true_is_overridden;
void __seagrass_required_true(int check);

#endif /* TEST */

#endif /* _SEA_TURTLE_TEST_WRAP_H_ */
