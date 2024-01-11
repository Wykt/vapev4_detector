#include <iostream>
#include <Windows.h>
#include "detector.h"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved )  // reserved
{
    if(fdwReason == DLL_PROCESS_ATTACH) {
        HANDLE handle = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(detector::main), hinstDLL, 0, nullptr);
        CloseHandle(handle);
    }

    return TRUE;
}
