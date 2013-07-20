#include "pause.h"
#include "curses.h"
#include "globals.h"

// Quit the shell -- also try to gracefully shutdown if possible
void quit(int code) {
        int i;

        for (i=0; i < max_children; i++)
               if (children[i] > 0) waitpid(children[i], NULL, 0);

	#ifdef CURSES
	curses_end();
	#endif

	free(current_cmd);

        exit(code);
}

