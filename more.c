#include "more.h"

char* open_more_with(char* path) {
    int rc;
    char* ret = "";
    pid_t pid = fork();
    if (pid == 0) {
        rc = execl("/usr/bin/more", "more", path, (char*)NULL);
        exit(0);
    }
    if (rc != 0)
        ret = "Could not open more with exec.\n";
    int status;
    wait(&status);
    return ret;
}