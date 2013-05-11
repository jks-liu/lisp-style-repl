#include "lisp-style-repl.h"

/* interpreter status */
static struct {
    uint_fast8_t max_command_length;
    struct Lsr_setting *setting_p;
} g_status = {0u, NULL};


