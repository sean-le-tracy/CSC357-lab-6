#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("please enter exactly one argument\n");
        return 1;
    }

    char *ptr;
    long val = strtol(argv[1], &ptr, 10);

    if (*ptr != '\0') {
        printf("please enter an integer\n");
        return 1;
    }

    if (val < 1) {
        printf("please enter a non-zero positive integer\n");
        return 1;
    }

    for (int i = 2; i <= val; i += 2) {
        printf("%d\n", i);
    }
}