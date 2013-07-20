#include "pause.h"
#include "curses.h"

// BUILTIN: Pause the shell until STDIN presses ENTER
//  Also, SIGSTOP any backgrounded children and SIGCONT when we
// are ready.
int pause() {
    int i;

    for (i=0; i < max_children; i++) {
        if (children[i] > 0) kill(children[i], SIGSTOP);
    }

    PRINT("--pause--");
    #ifdef CURSES
    char str[1] = "";
    getstr(str);
    #else
    while(getc(stdin) != '\n') ; /* NOTHING */
    #endif

    for (i=0; i < max_children; i++) {
        if (children[i] > 0) kill(children[i], SIGCONT);
    }

    return 0;
}

