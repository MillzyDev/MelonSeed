#include <windows.h>

#define SEED_API extern "C" __declspec(dllexport)

SEED_API void init() {
    MessageBoxA(nullptr, "Inited", "Inited", MB_OK);
}

SEED_API void late_init() {
    MessageBoxA(nullptr, "Late Inited", "Late Inited", MB_OK);
}