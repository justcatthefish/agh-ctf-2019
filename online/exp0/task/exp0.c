// gcc ./exp0.c -no-pie -fno-stack-protector -o exp0
#include <stdio.h>
#include <stdlib.h>

void readFlag() {
    char buf[100] = {};
    FILE *fd = fopen("./flag.txt", "r");
    if(fd == NULL) {
        puts("Error reading flag");
        return;
    }
    fread(buf, 99, 1, fd);
    fclose(fd);
    printf("flag: %s", buf);
    exit(0);
}

int main(int argc, char const *argv[])
{
    char name[30];
    scanf("%s", name);
    printf("Hello %s\n", name);
    return 0;
}