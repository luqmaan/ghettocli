#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "pause.h"

char *current_cmd;

// Attempt to EXECUTE a program:
int exec(char *tmp) {
        pid_t child;
        char args[1024] = "", *ptr;
        char cmd[1024], cmdname[1024], path[1024];
        char *filesep = NULL;
        int ret, is_background = 0, i;

	// Copy argument into local variables for manipulating
        strncpy(cmd, tmp, 1024);
        strncpy(path, cmd, 1024);

        // determine if background or foreground...must be last character on line
        if (cmd[strlen(cmd)-1] == '&') {
		// set state and clear the & from command
                is_background = 1;
                cmd[strlen(cmd)-1] = 0;
        }

        // Before we exec, check for zombies!
        if (cur_children > 0) {
                for (i=0; i < max_children; i++) {
                        if (waitpid(children[i], NULL, WNOHANG) > 0) {
                                cur_children--;
                                children[i] = 0;
                        }
                }
        }

        if (cur_children > max_children) {
                printf("Sorry, too many children were spawned.\n");
                return -1;
        }

	// Begin process by forking
        child = fork();

        if (child == 0) {

                // Locate leading parh if provided in command by searching for last occurence of '/'
                ptr = path;
                do {
                        if (*ptr == '/') filesep = ptr+1;
                        ptr++;
                } while (ptr != NULL && *ptr != 0);
                if (filesep != NULL) *filesep = 0;
                else filesep = path;

		// Now, find the first space and copy whats left as the command arguments
                ptr = &cmd[filesep-path];
                do {
                        if (ptr != NULL && *ptr == ' ') {
                                *ptr = 0;
                                strncpy(args, ++ptr, 1024);
                                break;
                        }
                        ptr++;
                } while (ptr != NULL && *ptr != 0);

		// Since we need the command-name seperate for execl(), save it
                strncpy(cmdname, &cmd[filesep-path], 1024);

		// I implemented a getenv(PATH) algorithm manually, but decided to use execlp() for portability
                if (strlen(args) <= 0)
                        ret = execlp( cmd, cmdname, NULL );
                else
                        ret = execlp( cmd, cmdname, args, NULL );

                if (ret < 0) perror(current_cmd);
                exit(ret);
        }
        else if (child < 0) return -1; // Fork failed?!
        else if (is_background == 0) wait(NULL); // Parent process, and FOREGROUND state -- WAIT on child
        else if (is_background == 1) { 
		// Parent process, and BACKGROUND state -- try to add child PID to pool of children and return
                for (i=0; i < max_children; i++)
                        if (children[i] <= 0) break;

                if (i < max_children) children[i] = child;
                cur_children++;
        }

        return 0;
}


