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

    int cmd = hashify(input);

    if (cmd == hashify("quit") || cmd == hashify("exit")) {
        // return 1 to stop the main_loop
        return 1;
    }
    else if (cmd == hashify("help")) {
        help();
    }
    else if (cmd == hashify("ls")) {
        char* lines = ls();
        int i = 0;
        // for (i = 0; i < sizeof(lines) / sizeof(char); i++) {
        printw("%s\n", lines);
        // }
    }
    else if (cmd == hashify("clear")) {
        erase();
    }
    else if (cmd == hashify("cd")) {
        printw("cd");
    }
    else {
        printw("Unrecognized command: %s\n", input);
    }

    return 0;
}


void main_loop()
{
    char str[80];
    int quit = 0;
    while (1) {

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
    start_color();
    use_default_colors();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    main_loop();

    endwin();

    return 0;
}