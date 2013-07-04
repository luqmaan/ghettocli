#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "dir.h"


// http://stackoverflow.com/questions/7666509/hash-function-for-string
int hashify(char *str) {
    int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

void help()  {
    printw("2 chainz.\n");
}

int parse_input(char *input) {
    int in = hashify(input);

    if (in == hashify("quit") || in == hashify("exit")) {
        return 1;
    }
    else if (in == hashify("help")) {
        help();
    }
    else if (in == hashify("ls")) {
        char* lines = ls();
        int i = 0;
        // for (i = 0; i < sizeof(lines) / sizeof(char); i++) {
        printw("%s", lines);
        // }
    }

    return 0;
}


void main_loop()
{
    char str[80];
    int quit = 0;
    while (1) {

        attron(A_BOLD);

        printw("gcli \\$/ \\$/ > ");
        attroff(A_BOLD);
        refresh();

        getstr(str);

        quit = parse_input(str);

        if (quit)
            break;

        refresh();
    }
}

int main()
{
    // gcc -lncurses -Wall -o curse.out curse.c && ./curse.out
    // http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html

    initscr();
    raw();
    keypad(stdscr, TRUE);

    main_loop();

    endwin();

    return 0;
}