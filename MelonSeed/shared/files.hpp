#pragma once

#include <filesystem>

#ifdef MELON_SEED_EXPORT_SYMBOLS
#define MELON_SEED_EXPORT __declspec(dllexport)
#else
#define MELON_SEED_EXPORT
#endif


namespace melonseed::files {
    MELON_SEED_EXPORT std::filesystem::path get_game_dir();
    MELON_SEED_EXPORT std::filesystem::path get_melonseed_dir();
    MELON_SEED_EXPORT std::filesystem::path get_logs_dir();
    MELON_SEED_EXPORT std::filesystem::path get_mods_dir();
    MELON_SEED_EXPORT std::filesystem::path get_libs_dir();

    MELON_SEED_EXPORT std::filesystem::path get_latest_log_file();
}