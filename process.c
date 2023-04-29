#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    char foo[] = "roflcopter";

    printf("pid: %d\n", getpid());
    printf("address: %lx\n", (size_t)foo);
    printf("length: %lu\n", strlen(foo) + 1);

    getchar();

    return 0;
}