#include <windows.h>
#include <iostream>

DWORD WINAPI threadFunction(LPVOID lpParam) 
{
    for (int i = 0; i < 10; i++) {
        std::cout << "injected dll " << i << "\n";
        Sleep(1000);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    HANDLE hThread = NULL;
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            hThread = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);
            CloseHandle(hThread);
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

