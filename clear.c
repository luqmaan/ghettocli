
#ifdef CURSES
#else
#include <unistd.h>
#endif

// Try to clear the screen...
int clr_cmd() {

    #ifndef CURSES
	write(1,"\E[H\E[2J",7); // Without curses, try to use standard ANSI-style codes
    #else
	clear();	
    #endif

    return 0;
}

