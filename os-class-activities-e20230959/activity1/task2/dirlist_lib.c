#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void) {
    DIR *d = opendir(".");
    if (d == NULL) { perror("opendir"); return 1; }
    struct dirent *e;
    struct stat st;
    while ((e = readdir(d)) != NULL) {
        if (stat(e->d_name, &st) == 0)
            printf("%-30s %10ld bytes\n", e->d_name, (long)st.st_size);
    }
    closedir(d);
    return 0;
}
