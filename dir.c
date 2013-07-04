#include "dir.h"

// http://pubs.opengroup.org/onlinepubs/9699919799/functions/chdir.html#tag_16_57_06_01
int cd(const char* path) {
    int ret = 0;

    ret = chdir(path);
    if (ret)
        perror(NULL);

    return ret;
}

// http://pubs.opengroup.org/onlinepubs/009695399/functions/opendir.html
// http://pubs.opengroup.org/onlinepubs/009695399/basedefs/dirent.h.html
char* ls_path(const char* path) {
    char* ls_string = "";
    
    DIR* dir;
    struct dirent* dir_ent;
    
    dir = opendir(path);

    if (dir != NULL) {    
        while ( (dir_ent = readdir(dir)) != NULL) {
            size_t len1 = strlen(ls_string);
            size_t len2 = strlen(dir_ent->d_name);

            char* temp = (char*) malloc(len1 + len2 + 2);
            memcpy(temp, ls_string, len1);
            temp[len1] = '\n';
            memcpy(temp + len1 + 1, dir_ent->d_name, len2 + 1); // includes terminating null

            ls_string = temp;
            // printf("dir: %s   \tsize_t: %d  \ts: %s\n", dir_ent->d_name, (int)len2, temp);
        }
    }
    else {
        perror(NULL);
        ls_string = "Error";
    }

    return ls_string;
}

char* ls() {
    const char* path = "./";
    return ls_path(path);
}

char* cwd() {
    char* cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return getcwd(cwd, 1024);
    }
    else return "Error getting path\n";
}