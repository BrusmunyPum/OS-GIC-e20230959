#include <windows.h>
#include <string.h>

int main(void) {
    const char *msg = "Hello from the Windows API!\r\n";
    DWORD written;

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);   /* handle to the console */
    WriteFile(out, msg, (DWORD)strlen(msg), &written, NULL);
    return 0;
}
