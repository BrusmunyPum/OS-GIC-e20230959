#include <unistd.h>
#include <string.h>

int main(void) {
    const char *msg = "Hello from a system call!\n";
    write(1, msg, strlen(msg));   /* fd 1 = stdout */
    return 0;
}
