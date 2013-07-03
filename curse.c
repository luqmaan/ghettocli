#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

typedef struct hashed_inputs_struct {
    int input;
    int quit;
    int ls;
} hashed_inputs;

hashed_inputs HASHES;

// http://stackoverflow.com/questions/7666509/hash-function-for-string
int hashify(char *str) {
    int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

void ls() {

    printw("LS LSLS LSLSLSLSLSLSSLSLSLSLS");

}


int parse_input(char *input) {
    int in = hashify(input);

    if (in == HASHES.quit) {
        return 1;
    }
    else if (in == HASHES.ls) {
        ls();
    }

    return 0;
}


void fill_in_hash_struct() {
    HASHES.input = hashify("input");
    HASHES.quit = hashify("quit");
    HASHES.ls = hashify("ls");
}


void main_loop()
{
    int ch;
    char str[80];
    int quit = 0;
    while (1) {

        attron(A_BOLD);

        printw("gcli \\$/ > ");
        attroff(A_BOLD);
        refresh();

        getstr(str);

        int hash = hashify(str);
        mvprintw(LINES - 4, 0, "hash: %d", hash);

        quit = parse_input(str);
        if (quit)
            break;

        mvprintw(LINES - 2, 0, "You Entered: %s", str);
        refresh();
    }
}

int main()
{
    // gcc -lncurses -Wall -o curse.out curse.c && ./curse.out
    // http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html

    fill_in_hash_struct();
    initscr();
    raw();
    keypad(stdscr, TRUE);

    main_loop();

    endwin();

    return 0;
}