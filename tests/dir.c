#include "../dir.h"

int main() {
    printf("hai\n");

    printf("current dir is: %s\n", cwd());
    printf("ls returned: %s\n", ls());

    cd("/Users");
    printf("current dir is: %s\n", cwd());
    ls();
    cd("/wioejfowiejf");
    ls_path("/wefwefw");

    return 0;

}


