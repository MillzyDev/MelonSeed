#pragma once

#ifdef MELON_SEED_EXPORT_SYMBOLS
#define MELON_SEED_EXPORT __declspec(dllexport)
#else
#define MELON_SEED_EXPORT
#endif

#include <fstream>
#include <format>
#include <string>

namespace melonseed {
    class logger {
    private:
        static std::ofstream log_file_stream;

        static void log_info(std::string name_section, std::string text);
        static void log_warning(std::string name_section, std::string text);
        static void log_error(std::string name_section, std::string text);

        std::string name;

    public:
        MELON_SEED_EXPORT explicit logger(std::string name);

        MELON_SEED_EXPORT static void initialise_logger();

        template<typename... Args>
        inline void info(std::format_string<Args...> format, Args &&...args) {
            std::string message = std::vformat(format.get(), std::make_format_args(args...));
            log_info(name, message);
        }

        template<typename... Args>
        inline void warning(std::format_string<Args...> format, Args &&...args) {
            std::string message = std::vformat(format.get(), std::make_format_args(args...));
            log_warning(name, message);
        }

        template<typename... Args>
        inline void error(std::format_string<Args...> format, Args &&...args) {
            std::string message = std::vformat(format.get(), std::make_format_args(args...));
            log_error(name, message);
        }
    };
}