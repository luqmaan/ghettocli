#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

char* current_dir;

int handle_error(char* source, int ret_code) {
    printf("Error: %s . Error code: %d", source, ret_code);
    return ret_code;
}

// http://pubs.opengroup.org/onlinepubs/9699919799/functions/chdir.html#tag_16_57_06_01
int cd(const char* path) {
    int ret = 0;

    ret = chdir(path);
    if (ret)
        return handle_error("No such path", ret);

    return ret;
}


int ls() {
    return ls_path(current_dir);
}

// http://pubs.opengroup.org/onlinepubs/009695399/functions/opendir.html
// http://pubs.opengroup.org/onlinepubs/009695399/basedefs/dirent.h.html
int ls_path(const char* path) {
    int ret = 0;

    DIR* dir;
    struct dirent* dir_ent;
    
    dir = opendir(path);
    
    while ( (dir_ent = readdir(dir)) != NULL) {
        printf("%s\n", dir_ent->d_name);
    }
    
    return ret;
}


int main() {
    printf("hai\n");

    current_dir = "./";

    ls();
    cd("/Users/");
    ls();
    ls_path("/");

    return 0;
}


