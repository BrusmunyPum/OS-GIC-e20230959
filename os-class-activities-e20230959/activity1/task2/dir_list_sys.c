#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void) {
    DIR *d = opendir(".");
    if (d == NULL) { write(2, "opendir failed\n", 15); return 1; }
    struct dirent *e;
    struct stat st;
    char line[512];
    while ((e = readdir(d)) != NULL) {
        if (stat(e->d_name, &st) == 0) {
            int len = snprintf(line, sizeof line, "%-30s %10ld bytes\n",
                               e->d_name, (long)st.st_size);
            write(1, line, len);
        }
    }
    closedir(d);
    return 0;
}
