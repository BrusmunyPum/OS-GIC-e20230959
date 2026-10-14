#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    const char *text = "Hello from the C library!\n";
    const char *done = "File created successfully.\n";

    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { write(2, "open failed\n", 12); return 1; }
    write(fd, text, strlen(text));
    close(fd);
    write(1, done, strlen(done));
    return 0;
}
