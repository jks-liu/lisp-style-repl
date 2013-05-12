#include "lisp-style-repl.h"
#include <stdio.h>

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
    struct Lsr_command Lsr_commands[] =
        {{"copyright", copyright,
          (const char *[]){"Show copyright\n",
                           "Show Information like author and license.\n"}},
         {NULL, NULL, NULL}};
    char *args[5];
    struct Lsr_setting lsr = {Lsr_commands, put_str, args, true};
    put_str("Initializing\n");
    lsr_init(&lsr);
    put_str("Executing\n");
    char command[2][20] = {"(copyright)", "a wrong example"};
    lsr_execute(command[0]);
    return lsr_execute(command[1]);    
}



