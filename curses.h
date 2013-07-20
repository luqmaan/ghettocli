
#ifdef CURSES

#define PRINT(format, ...) printw(format, ##__VA_ARGS__)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdarg.h>

int curses_init();
int curses_end();
void curses_loop();
void curses_prompt();

FILE *input;
char *current_cmd;
char *current_dir;

#else

#define PRINT(format, ...) printf(format, ##__VA_ARGS__)

#endif

