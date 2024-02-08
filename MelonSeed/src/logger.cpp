#include "logger.hpp"
#include "files.hpp"

#include "termcolor/termcolor.hpp"

#include <chrono>
#include <iostream>

namespace melonseed {
    std::ofstream logger::log_file_stream;

    void logger::initialise_logger() {
        std::filesystem::path latest_log = files::get_latest_log_file();

        if (exists(latest_log)) {
            std::filesystem::file_time_type last_write = std::filesystem::last_write_time(latest_log);
            std::string log_file_name = std::format(
                    "MelonSeed_{:%Y-%m-%d_%H-%M-%S}.log",
                    std::chrono::time_point_cast<std::chrono::milliseconds>(last_write)
                    );

            std::filesystem::path full_log_file_name = files::get_logs_dir() / log_file_name;
            std::filesystem::rename(latest_log, full_log_file_name);
        }

        log_file_stream = std::ofstream(latest_log);
        log_file_stream << std::endl;
    }

    void logger::log_info(std::string name_section, std::string text) {
        auto now = std::chrono::system_clock::now();
        std::string timestamp = std::format(
                "{0:%H:%M:%S}",
                std::chrono::time_point_cast<std::chrono::milliseconds>(now)
        );

        log_file_stream << "[" << timestamp << "] [" << name_section << "] " << text << std::endl;

        std::cout
            << termcolor::white << "["
            << termcolor::bright_green << timestamp
            << termcolor::white << "] ["
            << termcolor::cyan << name_section
            << termcolor::white << "] "
            << text << std::endl;
    }

    void logger::log_warning(std::string name_section, std::string text) {
        auto now = std::chrono::system_clock::now();
        std::string timestamp = std::format(
                "{0:%H:%M:%S}",
                std::chrono::time_point_cast<std::chrono::milliseconds>(now)
                );

        log_file_stream << "[" << timestamp << "] [" << name_section << "] " << text << std::endl;

        std::cout
                << termcolor::white << "["
                << termcolor::bright_green << timestamp
                << termcolor::white << "] ["
                << termcolor::cyan << name_section
                << termcolor::white << "] "
                << termcolor::bright_yellow << text << std::endl;
    }

    void logger::log_error(std::string name_section, std::string text) {
        auto now = std::chrono::system_clock::now();
        std::string timestamp = std::format(
                "{0:%H:%M:%S}",
                std::chrono::time_point_cast<std::chrono::milliseconds>(now)
        );

        log_file_stream << "[" << timestamp << "] [" << name_section << "] " << text << std::endl;
        std::cout << termcolor::red << "[" << timestamp << "] [" << name_section << "] " << text << std::endl;
    }

    logger::logger(std::string name) {
        std::replace(name.begin(), name.end(), ' ', '_');
        this->name = std::string_view(name);
    }
}
