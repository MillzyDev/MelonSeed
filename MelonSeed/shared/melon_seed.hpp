#pragma once

#ifdef MELON_SEED_EXPORTS
#define SEED_EXPORT __declspec(dllexport)
#else
#define SEED_EXPORT
#endif
