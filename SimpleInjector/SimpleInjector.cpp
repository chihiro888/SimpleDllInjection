#include <Windows.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    DWORD pId = 25764;
    char dllToInject[] = "C:\\Users\\dev\\source\\repos\\SimpleDllInjection\\x64\\Debug\\SimpleDll.dll";
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pId);

    if (!processHandle) {
        return 0;
    }

    LPVOID loadLibAddress = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    LPVOID baseAddress = VirtualAllocEx(processHandle, NULL, strlen(dllToInject), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    WriteProcessMemory(processHandle, baseAddress, dllToInject, strlen(dllToInject), NULL);
    HANDLE remoteThreadHandle = CreateRemoteThread(processHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibAddress, baseAddress, 0, NULL);
    WaitForSingleObject(remoteThreadHandle, INFINITE);
    VirtualFreeEx(processHandle, baseAddress, strlen(dllToInject), MEM_RELEASE);
    CloseHandle(remoteThreadHandle);
    CloseHandle(processHandle);
}
