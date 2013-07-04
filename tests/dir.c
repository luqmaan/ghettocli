#include "../dir.h"

int main() {
    printf("hai\n");

    char* l = ls();
    printf("ls returned: %s\n", l);

    printf("%d\n", (int) strlen(l));

    // cd("/Users/");
    // ls();
    // cd("/wioejfowiejf");
    // ls_path("/wefwefw");

    return 0;

}


