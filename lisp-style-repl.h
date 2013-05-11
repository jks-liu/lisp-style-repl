#ifndef LISP_STYLE_REPL_H
#define LISP_STYLE_REPL_H

#include <stdtypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct Lsr_command {
    const char *command_name;
    int (*handler)(int argc, char *argv[]);
    const char *manual;
};


struct Lsr_setting {
    uint_fast8_t command_line_length; /* include args & the NULL of string */
    const struct Lsr_command *command_table;
};

void lsr_init(const struct Lsr_setting *setting);
int lsr_execute(char *command); /* command will be modified */


    

#ifdef __cplusplus
}
#endif 

#endif /* LISP_STYLE_REPL_H */

