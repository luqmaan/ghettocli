/* ghettoCLI  */
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>


#include "version.h"

#include "dir.h"
#include "help.h"
#include "more.h"
#include "pause.h"
#include "quit.h"
#include "clear.h"
#include "echo.h"
#include "exec.h"

#ifdef STACKTRACE
#include "stacktrace.h"
#endif

#ifdef CURSES
#include "curses.h"
#endif

#include "globals.h"

// Given a formatted string, replace special variables with their values
// %uid = $ if non-root, # if root
// %pwd = current directory
char *make_prompt(const char *format) {
    char prompt[1024] = "";
    char temp[1024] = "";
    char *ptr;

    strncpy(prompt, format, 1024);

    if ((ptr=strstr(prompt, "%%uid")) != NULL) {
        strncpy(temp, ptr+5, 1024);

        snprintf(ptr, 1024 - (prompt-ptr), "%s%s", (getuid() == 0) ? "#" : "$", temp);
    }

    if ((ptr=strstr(prompt, "%%pwd")) != NULL) {
        strncpy(temp, ptr+5, 1024);

        snprintf(ptr, 1024 - (prompt-ptr), " %s%s", current_dir, temp);
    }

    return prompt;
}


// This is basically STRNCMP() except instead of returning the match,
// we return a pointer to the REMAINDER of the string (arguments) or NULL
char *test_cmd(const char *buf, const char *cmd) {
        int c1, c2, flag;

        if (buf == NULL || cmd == NULL) return NULL;

        // Iterate through each string and check if characters match
        do {
                c1 = *buf++;
                c2 = *cmd++;
                flag = (c1 == c2);

                // Try to be case-insensitive
                if (!flag) flag = (c1+32 == c2);
                if (!flag) flag = (c1 == c2+32);
        } while ( flag && c1 != 0 && c2 != 0);

        // if we reached the end of CMD, but not BUF, then we matched so return the arguments left in BUF
        if (c2 == 0 && c1 != 0) return buf;

        return NULL;
}

void parse_input(char *buf) {
	char *ptr;

        // Either it matches completely (case-insensitive)

        // OR test_cmd() matches the COMMAND and returns a pointer to the arguments
        if (strncasecmp(buf, "quit", 4) == 0) quit(0);
        else if (strncasecmp(buf, "pwd", 3) == 0) pwd();
        else if (strcasecmp(buf, "ls") == 0) ls(current_dir);
	else if (strcasecmp(buf, "cd") == 0) cd("");
        else if (strcasecmp(buf, "dir") == 0) ls(current_dir);
        else if (strncasecmp(buf, "cls", 3) == 0) clr_cmd();
        else if (strncasecmp(buf, "clear", 5) == 0) clr_cmd();
        else if (strncasecmp(buf, "pause", 5) == 0) pause();
        else if (strncasecmp(buf, "help", 4) == 0) help();
        else if ((ptr=test_cmd(buf, "cd")) != NULL) cd(ptr);
        else if ((ptr=test_cmd(buf, "ls")) != NULL) ls_path(ptr);
        else if ((ptr=test_cmd(buf, "dir")) != NULL) ls_path(ptr);
        else if ((ptr=test_cmd(buf, "echo")) != NULL) echo_cmd(ptr);
        else exec(current_cmd); // Exec is the catch-all
}

// Main GHETTO entry point :-)
int main(int argc, char *argv[]) {

    #ifndef CURSES
    // Default ANSI colorized shell prompt
    const char format[1024] = "\x1b[0;1mgcli\x1b[33m\\\x1b[32;1m%%uid\x1b[33;1m/\x1b[0;1m%%pwd\x1b[33;1m>\x1b[00m ";
    char buf[1024] = "";
    #endif

    // Setup some initial variables
    current_dir = getcwd(NULL, 1024);
    current_cmd = (char*)malloc(sizeof(char)*1024);
    input = stdin; // Until getopt tells us differently
    cur_children = 0;
    max_children = MAX_CHILDREN;

    int opt;
    while ((opt = getopt(argc, argv, "vf:")) != -1) {
        switch (opt) {
        case 'v':
                printf("%s: %d.%d\n", _GHETTO_NAME_, _GHETTO_VER_MAJOR_, _GHETTO_VER_MINOR_);
                exit(0);
                break;
        case 'f':
                input = fopen(optarg, "r+");
                if (input == NULL) err(EXIT_FAILURE, "fopen");
                break;
        default:
                fprintf(stderr, "Usage: %s [-v] [-f FILENAME]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Treat ONE extra argument as a batchfile, else Usage()
    if (argc == 2 && argv[1][0] != '-') {
        input = fopen(argv[1], "r+");
        if (input == NULL) err(EXIT_FAILURE, "fopen");
    }

    #ifdef CURSES
    curses_init();
	
    printw("hai\n");

    curses_loop();

    #else
    printf("\x1b[31;1mhai\x1b[0m\n");

    // main I/O loop
    do {
        buf[0] = 0; // clear previous line

        // If we have a user, make it pretty
        if (input == stdin) {
                printf("%s", make_prompt(format));
        }

        fgets(buf, 1024, input);
        if (buf == NULL || strlen(buf) <= 0) break; // fgets() failed?

        // kill trailing \n
        if (buf[strlen(buf)-1] == '\n')
                buf[strlen(buf)-1] = 0;

        // We aint got no time for "Empty lines"
        if (strlen(buf) <= 0) continue;

        // Save this command in the global buffer in case we want to bitch out the user later :P
        strncpy(current_cmd, buf, 1024);

        // Now we check for valid commands...
	parse_input(buf);

    }
    while (1);

    #endif

    fclose(input);

    quit(0);

    return 0;

}

