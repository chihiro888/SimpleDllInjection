#include <Windows.h>
#include <iostream>

int main()
{
    for (int i = 0; i < 100; i++) {
        std::cout << "Hello World!" << std::endl;
        Sleep(1000);
    }
}
