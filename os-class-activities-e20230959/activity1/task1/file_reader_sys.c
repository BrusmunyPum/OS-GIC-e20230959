#include <fcntl.h>
#include <unistd.h>

int main(void) {
    char buf[256];
    ssize_t n;
    int fd = open("output.txt", O_RDONLY);
    if (fd < 0) { write(2, "open failed\n", 12); return 1; }
    while ((n = read(fd, buf, sizeof buf)) > 0)
        write(1, buf, n);
    close(fd);
    return 0;
}
