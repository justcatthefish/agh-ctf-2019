// gcc ./exp2.c -no-pie -fno-stack-protector -z execstack -o exp2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    char name[30] = {};

    while(strncmp(name, "exit", 4)) {
        puts("Next name, please");
	read(0, name, 7331);
        printf("Hello ");
        printf(name);
        puts("");
    }

    return 0;
}
