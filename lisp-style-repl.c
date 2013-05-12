#include "lisp-style-repl.h"
#include <string.h>

/* interpreter status */
static struct {
    size_t max_arg_length;
    struct Lsr_setting *setting_p;
} g_status = {0u, NULL};

void lsr_init (struct Lsr_setting *restrict setting) {
    const struct Lsr_command *ct = setting->command_table;
    size_t l = 0;
    while (ct->command_name) {
        l = strlen(ct->command_name);
        g_status.max_arg_length = l > g_status.max_arg_length ?
            l : g_status.max_arg_length;
        ++ct;
    }
        
    g_status.setting_p = setting;
}

int lsr_execute(char *restrict command) {
    bool begin_of_str = true;
    int argc = 0;
    while (*command) {
        switch (*command) {
        case ')':               /* No break */
        case '(':               /* No break */
        case ' ':
            begin_of_str = true;
            *command = '\0';
            break;
        default:
            if (begin_of_str) {
                begin_of_str = false;
                g_status.setting_p->argv[argc++] = command;
            }
            break;
        } /* switch */
        ++command;
    } /* while */
    const struct Lsr_command *ct = g_status.setting_p->command_table;
    int return_status = LSR_ERR_NO_COMMAND;
    int command_return_status = 0;
    while (ct->command_name) {
        if (strncmp(ct->command_name, g_status.setting_p->argv[0],
                    g_status.max_arg_length) == 0) {
            command_return_status = (*ct->handler)(argc, g_status.setting_p->argv);
            return_status = command_return_status == 0 ? 0 : LSR_ERR_COMMAND_ERR;
            break;
        }
        ++ct;
    }
    
    int (*put_str)(const char *) = g_status.setting_p->put_str;
    put_str("Execute command: ");
    put_str(g_status.setting_p->argv[0]);
    put_str(". ");
    if (g_status.setting_p->use_color) {
        if (return_status == 0) {
            put_str("\x1b[32;1m");
        } else {
            put_str("\x1b[31;1m");
        }
    }
    switch (return_status) {
    case 0:
        put_str("Success.\n");
        break;
    case LSR_ERR_NO_COMMAND:
        put_str("Fail: command not found.\n");
        break;
    case LSR_ERR_COMMAND_ERR:
        put_str("Fail: command execute with a error.\n");
        break;
    default:
        return_status = LSR_ERR_OTHER;
        put_str("Fail: sorry, can not find the reason.\n");
        break;
    }
    put_str("\x1b[0m");
    return return_status;
}




