#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "wrap.h"

bool seagrass_required_true_is_overridden = false;
extern void __real_seagrass_required_true(int check);
void __wrap_seagrass_required_true(int check) {
    if (!seagrass_required_true_is_overridden) {
        __real_seagrass_required_true(check);
    } else {
        function_called();
    }
}
