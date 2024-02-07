#include "files.hpp"

#include <filesystem>
#include <windows.h>

namespace melonseed::files {
    std::filesystem::path get_game_dir() {
        static std::filesystem::path dir;

        if (dir.empty()) {
            char executable[MAX_PATH];
            (void) GetModuleFileNameA(nullptr, executable, MAX_PATH);
            dir = std::filesystem::path(executable).parent_path();
        }

        return dir;
    }

    std::filesystem::path get_melonseed_dir() {
        static std::filesystem::path dir = get_game_dir() / "MelonSeed";
        return dir;
    }

    std::filesystem::path get_logs_dir() {
        static std::filesystem::path dir = get_melonseed_dir() / "logs";
        return dir;
    }

    std::filesystem::path get_mods_dir() {
        static std::filesystem::path dir = get_melonseed_dir() / "mods";
        return dir;
    }

    std::filesystem::path get_libs_dir() {
        static std::filesystem::path dir = get_melonseed_dir() / "libs";
        return dir;
    }

    std::filesystem::path get_latest_log_file() {
        static std::filesystem::path file = get_melonseed_dir() / "latest.log";
        return  file;
    }
}