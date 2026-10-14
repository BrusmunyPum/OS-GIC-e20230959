#include <fcntl.h>
#include <unistd.h>

int main(void) {
    char buf[4096];
    ssize_t n;

    int in = open("result.txt", O_RDONLY);
    if (in < 0) { write(2, "open src failed\n", 16); return 1; }

    int out = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) { write(2, "open dst failed\n", 16); return 1; }

    while ((n = read(in, buf, sizeof buf)) > 0)
        write(out, buf, n);

    close(in);
    close(out);
    return 0;
}
