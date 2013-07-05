#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

FILE* input;
char* current_dir;
char* current_cmd;

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

int ls(char *path) {
    return ls_path(path);
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

void quit(int code) {
	// XXX kill children

	exit(code);
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

// copied a strncmp() implementation but return a pointer to the remainder of string after matching the beginning to cmd
char *test_cmd(const char *buf, const char *cmd) {
	int c1, c2;

	if (buf == NULL || cmd == NULL) return NULL;

	do {
		c1 = *buf++;
		c2 = *cmd++;
	} while ( (c1 == c2) && c1 != 0 && c2 != 0);

	if (c2 == 0 && c1 != 0) return buf;

	return NULL;
}

int main(int argc, char *argv[]) {
    const char format[1024] = "gcli\\%%uid/%%pwd> ";
    char buf[1024] = "";
    char *ptr;

    // XXX track open children for pause() etc
    pid_t children[1024];
    current_dir = getcwd(NULL, 1024);
    input = stdin; // Until getopt tells us differently

    int flags, opt;
    while ((opt = getopt(argc, argv, "vf:")) != -1) {
	switch (opt) {
	case 'v':
		printf("ghettocli: 0.1\n");
		exit(0);
		break;
	case 'f':
		input = fopen(optarg, "r+");
		if (input == NULL) err("fopen");
		break;
	default:
		fprintf(stderr, "Usage: %s [-v] [-f FILENAME]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
    }
    
    printf("hai\n");

    do {
	buf[0] = 0; // clear previous line
	if (input == stdin) printf("%s", make_prompt(format));
	fgets(buf, 1024, input);

	if (buf == NULL || strlen(buf) <= 0) break;

	buf[strlen(buf)-1] = 0; // kill trailing \n

	// XXX hmm should we implement a case-insensitive strcmp?
	if (strcmp(buf, "quit") == 0) quit(0);

	// pwd, cd, ls, dir
	current_cmd = buf;

	if (strcmp(buf, "pwd") == 0) pwd();
	else if (strcmp(buf, "ls") == 0) ls(current_dir);
	else if (strcmp(buf, "dir") == 0) ls(current_dir);
	else if ((ptr=test_cmd(buf, "cd")) != NULL) cd(ptr);
	else if ((ptr=test_cmd(buf, "ls")) != NULL) ls(ptr);
	else if ((ptr=test_cmd(buf, "dir")) != NULL) ls(ptr);
	else echo(buf);

    }
    while (1);

    fclose(input);

    return 0;

}


