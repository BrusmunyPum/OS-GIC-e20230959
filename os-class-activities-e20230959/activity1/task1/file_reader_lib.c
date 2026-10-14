#include <stdio.h>

int main(void) {
    char line[256];
    FILE *fp = fopen("output.txt", "r");
    if (fp == NULL) { perror("fopen"); return 1; }
    while (fgets(line, sizeof line, fp) != NULL)
        printf("%s", line);
    fclose(fp);
    return 0;
}
