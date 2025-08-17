// SOFTWARE\Microsoft\Windows\CurrentVersion\Run
// Creates persistence in that path, once restarted it opens a calculator; displays a messageBox once ran (Win32)
// ------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <windows.h>

void registryCreate(LPCSTR path, LPCSTR name, DWORD type);
void messagebox(LPCSTR message, LPCSTR title);

int main() {
    int Persistence { 1 };
    int MessageBox { 1 };

    switch(Persistence) {
        case 1:
            registryCreate("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", "calculator", REG_SZ);
            break;
        case 2:
            break;
    }

    switch(MessageBox) {
        case 1:
            messagebox("hey there", "i love calculators");
            break;
        case 2:
            break;
    }

    return 0;
}

void messagebox(LPCSTR message, LPCSTR title) {
    MessageBoxA(NULL, message, title, MB_OK);
}

void registryCreate(LPCSTR path, LPCSTR name, DWORD type) {
    HKEY hKey;

    LSTATUS accessPath = RegOpenKeyExA(
        HKEY_CURRENT_USER,
        path,
        0,
        KEY_ALL_ACCESS,
        &hKey
    );
    switch(accessPath) {
        case ERROR_SUCCESS:
            std::cout << "Accessed the path" << std::endl;
            break;
        default:
            std::cout << "Failed to access path" << std::endl;
            RegCloseKey(hKey);
            break;
    }

    LSTATUS setValue = RegSetValueExA(
        hKey,
        name,
        0,
        type,
        (LPBYTE)"C:\\Windows\\System32\\calc.exe",
        sizeof("C:\\Windows\\System32\\calc.exe")
    );
    switch(setValue) {
        case ERROR_SUCCESS:
            std::cout << "Created key" << std::endl;
            break;
        default:
            std::cout << "Failed to create key" << std::endl;
            RegCloseKey(hKey);
            break;
    }

    RegCloseKey(hKey);
}
