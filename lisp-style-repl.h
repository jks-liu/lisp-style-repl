#ifndef LISP_STYLE_REPL_H
#define LISP_STYLE_REPL_H

#include <inttypes.h>
#include <stdbool.h>

/* Documents will be availabe in the README.md */

#ifdef __cplusplus
extern "C"
{
#endif

#define LSR_ERR_NO_COMMAND 1
#define LSR_ERR_COMMAND_ERR 2
#define LSR_ERR_OTHER 3

struct Lsr_command {
    const char *command_name;
    int (*handler)(int, char *[]);
    const char **manual;
};

struct Lsr_setting {
    // uint_fast8_t max_command_length; /* include args & the NULL of string */
    const struct Lsr_command *command_table;
    // uint_fast8_t max_num_of_command_line; /* Include the flag of end */
    int (*put_str)(const char *);
    char **argv;
    bool use_color;
};

void lsr_init(struct Lsr_setting *restrict setting);
int lsr_execute(char *restrict command); /* command will be modified */


    

#ifdef __cplusplus
}
#endif 

#endif /* LISP_STYLE_REPL_H */










