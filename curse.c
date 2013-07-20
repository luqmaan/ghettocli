#ifdef CURSES

#include <string.h>

#include "dir.h"
#include "curses.h"

void parse_input(char *buf); /* from myshell.c */


// http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
int curses_init() {

    initscr();
    raw();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    start_color();
    use_default_colors();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    return 0;
}

int curses_end() {
    endwin();
    return 0;
}

void curses_loop() {
    char str[1024];

    while (1) {
	str[0] = 0; // clear buffer

	if (input == stdin) curses_prompt();

        refresh();

	if (input == stdin) getstr(str);
	else {
	        fgets(str, 1024, input);
        	if (str == NULL || strlen(str) <= 0) break; // fgets() failed?
	}

        // kill trailing \n
        if (str[strlen(str)-1] == '\n')
                str[strlen(str)-1] = 0;

        // We aint got no time for "Empty lines"
        if (strlen(str) <= 0) continue;

	strncpy(current_cmd, str, 1024);

        parse_input(str);

        refresh();
    }
}

void curses_prompt() {
    printw("[");
    attron(COLOR_PAIR(2));
    printw("gcli");
    attroff(COLOR_PAIR(2));
    printw(":%s] ", current_dir);
    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    printw("\\$/\\$/");
    attroff(COLOR_PAIR(1));
    printw(" > ");
    attroff(A_BOLD);
}

#endif
