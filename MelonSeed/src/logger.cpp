#include "logger.hpp"
#include "files.hpp"

#include <chrono>
#include <iostream>

namespace melonseed {
    void logger::initialise_logger() {
        std::filesystem::path latest_log = files::get_latest_log_file();

        if (exists(latest_log)) {
            std::filesystem::file_time_type last_write = std::filesystem::last_write_time(latest_log);
            std::string log_file_name = std::format("MelonSeed_{:%Y-%m-%d_%H-%M-%S}", last_write);
            std::filesystem::path full_log_file_name = files::get_logs_dir() / log_file_name;

            std::filesystem::rename(latest_log, full_log_file_name);
        }

        log_file_stream = std::ofstream(latest_log);
        log_file_stream << std::endl;
    }
}
