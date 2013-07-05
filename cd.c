#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

char* current_dir;

// http://pubs.opengroup.org/onlinepubs/9699919799/functions/chdir.html#tag_16_57_06_01
int cd(const char* path) {
    int ret = 0;
    char prefix[1024];

    snprintf(prefix, 1024, "cd %s", path);

    ret = chdir(path);
    if (!ret)
        current_dir = getcwd(NULL, 1024);

    if (ret)
        perror(prefix);
   
    return ret;
}

// http://pubs.opengroup.org/onlinepubs/009695399/functions/opendir.html
// http://pubs.opengroup.org/onlinepubs/009695399/basedefs/dirent.h.html
int ls_path(const char* path) {
    int ret = 0;
    char prefix[1024];

    snprintf(prefix, 1024, "ls %s", path);

    DIR* dir;
    struct dirent* dir_ent;
    
    dir = opendir(path);

    if (dir != NULL) {    
        while ( (dir_ent = readdir(dir)) != NULL) {
            printf("%s\n", dir_ent->d_name);
        }
    }
    else {
        perror(prefix);
        ret = 1;
    }

    return ret;
}

int ls() {
    return ls_path(current_dir);
}

int pwd() {
    printf( "%s\n", current_dir );
    return 0;
}

int echo(const char *buf) {
    printf("%s\n", buf);
    return 0;
}

int help() {

    return 0;
}

int clr() {

    return 0;
}

int pause() {

    return 0;
}

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

int main() {
    const char format[1024] = "gcli\\%%uid/%%pwd> ";
    char *ptr, *prompt;
    char temp[1024] = "", buf[1024] = "";
    extern FILE *stdin;

    current_dir = getcwd(NULL, 1024);

    prompt = make_prompt(format);

    printf("hai\n");

    pwd();
    ls();
    cd("/Users/");
    ls();
    cd("/wioejfowiejf"); 
    ls_path("/wefwefw");
    cd("test");
    pwd();

    prompt = make_prompt(format);
    printf("%s", prompt);
    fgets(buf, 1024, stdin);

    echo(buf);

    return 0;

}


