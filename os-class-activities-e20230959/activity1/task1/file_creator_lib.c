#include <stdio.h>

int main(void) {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) { perror("fopen"); return 1; }
    fprintf(fp, "Hello from the C library!\n");
    fclose(fp);
    printf("File created successfully.\n");
    return 0;
}
