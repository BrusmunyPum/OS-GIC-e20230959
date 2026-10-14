/* file_creator_win.c - Task 1A with the Windows API (no POSIX, no stdio) */
#include <windows.h>
#include <string.h>

int main(void) {
    const char *text = "Hello from the C library!\n";
    const char *confirm = "File created successfully.\n";
    const char *errmsg = "CreateFile failed\n";
    DWORD written = 0;

    /* CreateFile with CREATE_ALWAYS = create, or overwrite if it exists
       (like open() with O_CREAT | O_TRUNC) */
    HANDLE hFile = CreateFileA("output.txt", GENERIC_WRITE, 0, NULL,
                               CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        WriteFile(GetStdHandle(STD_ERROR_HANDLE), errmsg,
                  (DWORD)strlen(errmsg), &written, NULL);
        return 1;
    }

    WriteFile(hFile, text, (DWORD)strlen(text), &written, NULL);
    CloseHandle(hFile);

    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), confirm,
              (DWORD)strlen(confirm), &written, NULL);
    return 0;
}
