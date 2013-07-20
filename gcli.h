/* ghettocli  */
// Define the program name and version #.# as constants for use later
#define _GHETTO_NAME_ "ghettocli"
#define _GHETTO_VER_MAJOR_ 0
#define _GHETTO_VER_MINOR_ 69 
#define _MAX_CHILDREN 5

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>

#include "stacktrace.h"

/* BUILTIN commands */
int cd(const char* path);
int ls_path(const char* path);
int ls();
int pwd();
int _echo(const char *buf);
int help();
int clr();
int show_children();
int pause();
void quit(int code);

/* Unkown commands */
int exec(char *tmp);

/* Set up, receive, parse input */
char *make_prompt(char *prompt, const char *format);
char *test_cmd(char *buf, const char *cmd);
void ctl_c_handler(int s);
void ctl_d_handler(int s);
void trim(char * s);
