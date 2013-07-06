#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdarg.h>
#include "dir.h"
#include "more.h"

#define MAX_ARGS    32

int hashify(char *str);
int parse_input(char *input);
void line_prefix();
void main_loop();

int main()
{
    // gcc -lncurses -Wall -o curse.out curse.c && ./curse.out
    // http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html

    initscr();
    raw();
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    main_loop();

    endwin();

    return 0;
}

void main_loop()
{
    char str[80];
    int quit = 0;
    while (1) {

        line_prefix();
        refresh();

        getstr(str);

        quit = parse_input(str);

        if (quit)
            break;

        refresh();
    }
}



// http://stackoverflow.com/questions/7666509/hash-function-for-string
int hashify(char *str) {
    int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

int cmd_match(const char *cmd,...) {
    // https://github.com/torvalds/linux/blob/8a72f3820c4d14b27ad5336aed00063a7a7f1bef/tools/perf/util/exec_cmd.c#L129

    int argc;
    const char* argv[MAX_ARGS + 1];
    const char* arg;
    va_list param;

    va_start(param, cmd);
    argv[0] = cmd;

    argc = 1;
    while (argc < MAX_ARGS) {
        arg = argv[argc++] = va_arg(param, char*);
        if (!arg)
            break;
        if (strcmp(cmd, (char* )arg) == 0) {
            // found a match
            return 1;
        }
    }
    va_end(param);

    if (MAX_ARGS <= argc)
        printw("Error, too many arguments.");

    return 0;
}

int parse_input(char *input) {

    if (cmd_match(input,"quit", "exit", NULL)) {
        return 1; // return 1 to stop the main_loop
    }
    else if (cmd_match(input,"help", NULL)) {
        char* error = open_more_with("help.txt");
        if (! strcmp(error, ""))
            printw(error);
    }
    else if (cmd_match(input,"clear", "clr", NULL)) {
        erase();
    }
    else if (cmd_match(input,"ls", "dir", "cd", NULL)) {
        printw("%s\n", ls());
    }
    else if (cmd_match(input,"cd", NULL)) {
        printw("cd");
    }
    else if (cmd_match(input,"", NULL)) {
       // do nothing
    }
    else {
        printw("Unrecognized command: %s\n", input);
    }

    return 0;
}

void line_prefix() {
    printw("[");
    attron(COLOR_PAIR(2));
    printw("gcli");
    attroff(COLOR_PAIR(2));
    printw(":%s] ", cwd());
    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    printw("\\$/\\$/");
    attroff(COLOR_PAIR(1));
    printw(" > ");
    attroff(A_BOLD);
}
