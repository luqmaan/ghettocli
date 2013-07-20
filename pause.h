#ifndef _PAUSE_H_
#define _PAUSE_H_ 1

/* ghettoCLI  */
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CHILDREN 5

// Track backgrounded processes
pid_t children[MAX_CHILDREN];
int max_children;
int cur_children;



#endif
