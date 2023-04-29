#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("./reader <pid> <address> <length>\n");
        exit(1);
    }

    int pid = strtol(argv[1], NULL, 10);
    size_t addr = strtoul(argv[2], NULL, 16);
    int len = strtol(argv[3], NULL, 10);

    char* proc_mem = malloc(50);
    sprintf(proc_mem, "/proc/%d/mem", pid);

    printf("opening %s, address is %ld\n", proc_mem, addr);
    int mem_fd = open(proc_mem, O_RDONLY);

    if (mem_fd == -1) {
        printf("Could not open %s\n", proc_mem);
        exit(1);
    }

    char* buf = malloc(len+1);
    pread(mem_fd, buf, len, addr);

    printf("String at %lx in process %d is:\n", addr, pid);
    printf("%s\n", buf);

    free(buf);
    free(proc_mem);

    return 0;
}