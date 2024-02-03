#include <windows.h>

#include <iostream>

#define SEED_API extern "C" __declspec(dllexport)

SEED_API void Init() {
    std::cout << "Hi from C++!";
}

SEED_API void LateInit() {
    std::cout << "Hello again from C++!";
}