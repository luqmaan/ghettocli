#include "dir.h"
#include "echo.h"

#include "curses.h"

char* current_cmd;

// BUILTIN: try to change dir to argument
// http://pubs.opengroup.org/onlinepubs/9699919799/functions/chdir.html#tag_16_57_06_01
int cd(const char* path) {
    int ret = 0;

    if (strlen(path) <= 0) {
	echo_cmd(current_dir); // Per instructions
	return 0;
   }

    ret = chdir(path);

    // If success, change current_dir to where we really are
    if (!ret)
        current_dir = getcwd(NULL, 1024);

    // If failed, print well-formed error with prefix as the actual command for reference like a real shell does
    if (ret)
        perror(current_cmd); // XXX CURSES?

    return ret;
}

// BUILTIN: List directory supplied as argument
// http://pubs.opengroup.org/onlinepubs/009695399/functions/opendir.html
// http://pubs.opengroup.org/onlinepubs/009695399/basedefs/dirent.h.html
char* ls_path(const char* path) {
    DIR* dir;
    struct dirent* dir_ent;
    
    dir = opendir(path);

    if (dir != NULL) {    
        while ( (dir_ent = readdir(dir)) != NULL) {

	    PRINT("%s\n", dir_ent->d_name);

        }
    }
    else {
        perror(current_cmd);
    }

    return "";
}

char* ls() {
    const char* path = "./";
    return ls_path(path);
}

// Simply print the current directory
void pwd() {
    PRINT("%s\n", current_dir);
}


