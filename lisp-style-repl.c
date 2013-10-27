#include "lisp-style-repl.h"
#include <string.h>

static int get_last_return_value(int argc, char *argv[]);
static int help(int argc, char *argv[]);
static int manual(int argc, char *argv[]);

/* interpreter status */
static struct {
    size_t max_arg_length;
    int last_return_value;
    struct Lsr_setting *setting_p;
    struct Lsr_command *builtin_command_table;
} g_status = {
    0u,
    0,
    NULL,
    (struct Lsr_command []){
        {"$?",
         get_last_return_value,
         (const char *[]){
                "Last return value",
                NULL}},
        {"help",
         help,
         (const char *[]){
                "Show commands",
                NULL}},
        {"man",
         manual,
         (const char *[]){
                "Manual of a command",
                NULL}},
        {NULL, NULL, NULL}
    }
};

static unsigned char itostr_iterate(char *restrict str, int i) {
    *str = '0' + (i % 10);
    if (i / 10 == 0){
        return 0;
    } else {
        return itostr_iterate(str + 1, i / 10);
    }
}        
static void my_itostr(char *restrict str, int i) { /* i in [0, 256) */
    if (i < 0 || i > 255) {
        *str = '\0';
        return;
    }
    char s[4] = {0};
    itostr_iterate(s, i);
    int_fast8_t j = 0;
    for (; j < 4; ++j){
        if (*(s + 3 - j) != 0){
            *str++ = *(s + 3 - j);
            *str = '\0';
        }
    }
}    
        
static int get_last_return_value(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    char s[4];
    my_itostr(s, g_status.last_return_value);
    (*g_status.setting_p->put_str)(s);
    (*g_status.setting_p->put_str)("\n");
    return g_status.last_return_value;
}

static int help(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    int (*put_str)(const char *) = g_status.setting_p->put_str;
    const struct Lsr_command *ct = g_status.builtin_command_table;
    while (ct->command_name) {
        size_t len = strlen(ct->command_name);
        put_str(ct->command_name);
        for (size_t i = 0; i < g_status.max_arg_length + 1 - len; ++i) {
            put_str(" ");
        }
        put_str(ct->manual[0]);
        put_str("\n");
        ++ct;
    }
    ct = g_status.setting_p->command_table;
    while (ct->command_name) {
        size_t len = strlen(ct->command_name);
        put_str(ct->command_name);
        for (size_t i = 0; i < g_status.max_arg_length + 1 - len; ++i) {
            put_str(" ");
        }
        put_str(ct->manual[0]);
        put_str("\n");
        ++ct;
    }
    
    return 0;
}

static int manual(int argc, char *argv[]){
    int (*put_str)(const char *) = g_status.setting_p->put_str;
    if (argc != 2) {
        put_str("Bad option\n");
        return LSR_ERR_COMMAND_ERR;
    }

    int return_status = LSR_ERR_NO_COMMAND;
    const struct Lsr_command *ct = g_status.builtin_command_table;
    const char **manual;
    while (ct->command_name) {
        if (strncmp(ct->command_name, argv[1],
                    g_status.max_arg_length + 1) == 0) {
            manual = ct->manual;
            while (*manual != NULL) {
                put_str(*manual++);
                put_str("\n");
            }
            return_status = 0;
            break;
        }
        ++ct;
    }
    ct = g_status.setting_p->command_table;
    while (ct->command_name) {
        if (strncmp(ct->command_name, argv[1],
                    g_status.max_arg_length + 1) == 0) {
            manual = ct->manual;
            while (*manual != NULL) {
                put_str(*manual++);
                put_str("\n");
            }
            return_status = 0;
            break;
        }
        ++ct;
    }

    if (return_status != 0) {
        put_str(argv[1]);
        put_str(": No command\n");
    }

    return return_status;
}

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
static int get_argv(char *restrict command) {
    bool begin_of_str = true;
    int argc = 0;
    while (*command) {
        switch (*command) {
        case ')':               /* No break */
        case '(':               /* No break */
        case '\n':              /* No break */
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
    return argc;
}    
int lsr_execute(char *restrict command) {
    int argc = get_argv(command);
    if (argc == 0) {
        return 0;
    }
    int return_status = LSR_ERR_NO_COMMAND;
    const struct Lsr_command *ct = g_status.builtin_command_table;
    while (ct->command_name) {
        if (strncmp(ct->command_name, g_status.setting_p->argv[0],
                    g_status.max_arg_length + 1) == 0) {
            g_status.last_return_value =
                (*ct->handler)(argc, g_status.setting_p->argv);
            return_status = g_status.last_return_value == 0 ?
                0 : LSR_ERR_COMMAND_ERR;
            break;
        }
        ++ct;
    }
    ct = g_status.setting_p->command_table;
    while (ct->command_name) {
        if (strncmp(ct->command_name, g_status.setting_p->argv[0],
                    g_status.max_arg_length + 1) == 0) {
            g_status.last_return_value =
                (*ct->handler)(argc, g_status.setting_p->argv);
            return_status = g_status.last_return_value == 0 ?
                0 : LSR_ERR_COMMAND_ERR;
            break;
        }
        ++ct;
    }
    
    int (*put_str)(const char *) = g_status.setting_p->put_str;
    put_str("Exe ");
    put_str(g_status.setting_p->argv[0]);
    put_str(" ");
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
        put_str("Fail: no command.\n");
        break;
    case LSR_ERR_COMMAND_ERR:
        put_str("Fail: err.\n");
        break;
    default:
        return_status = LSR_ERR_OTHER;
        put_str("Fail\n");
        break;
    }
    put_str("\x1b[0m");
    return return_status;
}




