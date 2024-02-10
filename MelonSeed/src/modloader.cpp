#include "modloader.hpp"
#include "main.hpp"

namespace melonseed {
    void open_libs(std::filesystem::path libs_dir) {
        get_logger().info("Opening libraries: {}", libs_dir.string());

        for (const auto &file_entry : std::filesystem::directory_iterator{libs_dir}) {
            // only load the file if it's a file or a symlink, or a dll
            if (!(file_entry.is_regular_file() || file_entry.is_symlink()) || file_entry.path().extension().string() != ".dll") {
                continue;
            }

            const wchar_t *module_path = file_entry.path().c_str();
            HMODULE handle = LoadLibraryW(module_path);

            if (!handle) {
                DWORD error = GetLastError();

                std::string message;

                if (!error) {
                    get_logger().error("Failed to load library {} but no error was produced.", file_entry.path().string());
                } else {
                    LPSTR message_buffer;
                    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                                 nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                                 reinterpret_cast<LPSTR>(&message_buffer), 0, nullptr);

                    message = std::string(message_buffer, size);
                    get_logger().error("Failed to load {}", file_entry.path().string());
                    get_logger().error("Error code {:x}. {}", error, message);

                    LocalFree(message_buffer);
                }

                modloader::add_failed_lib({
                    file_entry.path().string(),
                    error,
                    message
                });

                SetLastError(0); // reset error for next time
                continue;
            }

            get_logger().info("Loaded library: {}", file_entry.path().string());

            modloader::add_loaded_lib({
                file_entry.path().string(),
                handle
            });
        }
    }

    void open_mods(std::filesystem::path mods_dir) {

    }
}