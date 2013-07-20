#include "help.h"
#include "version.h"

#include "curses.h"

// Print some basic instructions

// XXX Maybe ghetto-fy it with some ANSI color?!

int help() {

    PRINT("%s (%d.%d)\n", _GHETTO_NAME_, _GHETTO_VER_MAJOR_, _GHETTO_VER_MINOR_);
    PRINT("Usage: gcli [-v] [-f batchfile]\n");
    PRINT("Or: ghettocli batchfile\n");
    PRINT("-v: Print version\n");
    PRINT("batchfile: Read commands from file\n");
    PRINT("\n\nNo arguments starts a shell and reads commands from stdin:\n");
    PRINT("\n\nBuilt-in:\n");
    PRINT("LS, PWD, CD, ECHO, PAUSE, CLEAR, HELP, QUIT\n");
    PRINT("Accepts executable files by absolute path or will search through the PATH environment variable.\n");
    PRINT("Default execution is foreground, but may be placed in the background by appending a '&'\n");

    return 0;
}

