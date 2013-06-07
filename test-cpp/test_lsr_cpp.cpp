#include "lisp-style-repl.h"
#include <cstdio>

int copyright(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    printf ("Lisp style repl: A small command line interpreter.\n");
    printf ("Last version: https://github.com/jks-liu/lisp-style-repl\n");
    printf ("Copyright 2013. Jks Liu, http://jks-liu.github.io/\n");
    printf ("It's open source which is licensed under BSD.\n");
    return 0;
}

static int put_str(const char *str) {
    return printf ("%s", str);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    const char copyright_man0[] = "Show copyright";
    const char copyright_man1[] = "Show Information like author and license.";
    const char *copyright_manual[] = {copyright_man0, copyright_man1, 0};
    struct Lsr_command Lsr_commands[] =
        {{"copyright", copyright,
             copyright_manual},         
         {0, 0, 0}};
    char *args[5];
    struct Lsr_setting lsr = {Lsr_commands, put_str, args, true};
    lsr_init(&lsr);
    char command[255];
    while (printf("\x1b[32;1mjks@TEST:\x1b[34;1m~\n\x1b[0m# "),
           fgets(command, sizeof(command), stdin) != NULL){
        lsr_execute(command);
    }
    printf("exiting\n");

    return 0;
}



