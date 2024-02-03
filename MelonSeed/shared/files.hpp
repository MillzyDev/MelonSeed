#pragma once

namespace std::filesystem {
    class path;
}

namespace melon_seed::files {
    std::filesystem::path get_mods_path();
    std::filesystem::path get_libs_path();
    std::filesystem::path get_user_data_path();
    std::filesystem::path get_logs_path();
}