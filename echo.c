
#ifdef CURSES
#include "curses.h"
#else
#include <stdio.h>
#endif

// Just echo back the argument
int echo_cmd(const char *buf) {

	#ifdef CURSES
		printw("%s\n", buf);
	#else
		printf("%s\n", buf);
	#endif

	return 0;
}

