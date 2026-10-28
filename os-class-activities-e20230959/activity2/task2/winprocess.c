#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent process (PID: %lu) — creating child...\n", GetCurrentProcessId());

    /* Use full path to mspaint on Windows 11 */
    const char *appPath = "C:\\Users\\MUNY\\AppData\\Local\\Microsoft\\WindowsApps\\mspaint.exe";

    if (!CreateProcess(
            appPath,
            NULL,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi))
    {
        fprintf(stderr, "CreateProcess failed (error %lu).\n", GetLastError());
        return 1;
    }

    printf("Child process created!\n");
    printf("  Child PID:       %lu\n", pi.dwProcessId);
    printf("  Child Thread ID: %lu\n", pi.dwThreadId);

    printf("Parent: waiting for child (mspaint) to exit...\n");
    printf(">>> Open Task Manager now and take screenshots! <<<\n");
    printf(">>> Then close mspaint to finish. <<<\n");

    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("Parent: child has exited. Cleaning up.\n");

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
