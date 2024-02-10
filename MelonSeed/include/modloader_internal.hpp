#pragma once

#include <filesystem>

namespace melonseed {
    void open_libs(std::filesystem::path libs_dir);
    void open_mods(std::filesystem::path mods_dir);
}