#pragma once

#ifdef MELON_SEED_EXPORT_SYMBOLS
#define MELON_SEED_EXPORT __declspec(dllexport)
#else
#define MELON_SEED_EXPORT
#endif

#include <fstream>

namespace melonseed {
    class logger {
    private:
        static bool is_initialised;
        static std::ofstream log_file_stream;

    public:
        static void initialise_logger();
    };
}