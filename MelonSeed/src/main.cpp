#include "modloader.hpp"

#define SEED_API extern "C" __declspec(dllexport)

SEED_API void Init() {
    modloader_init();
}