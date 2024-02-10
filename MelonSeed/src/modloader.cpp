#include "modloader.hpp"
#include "main.hpp"

std::string get_error_message(DWORD error) {
    LPSTR message_buffer;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                 reinterpret_cast<LPSTR>(&message_buffer), 0, nullptr);

    std::string message(message_buffer, size);

    LocalFree(message_buffer);

    return message;
}

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
                    get_logger().error("Failed to load library {} but no error was produced.", file_entry.path().filename().string());
                } else {
                    message = get_error_message(error);
                    get_logger().error("Failed to load library {}", file_entry.path().filename().string());
                    get_logger().error("Error code {:x}. {}", error, message);
                }

                modloader::add_failed_lib({
                    file_entry.path(),
                    error,
                    message
                });

                SetLastError(0); // reset error for next time
                continue;
            }

            get_logger().info("Loaded library: {}", file_entry.path().string());

            modloader::add_loaded_lib({
                file_entry.path(),
                handle
            });
        }
    }

    void open_mods(std::filesystem::path mods_dir) {
        get_logger().info("Opening mods from: {}", mods_dir.string());

        for (const auto &file_entry : std::filesystem::directory_iterator(mods_dir)) {
            if (!(file_entry.is_regular_file() || file_entry.is_symlink()) || file_entry.path().extension().string() != ".dll") {
                continue;
            }

            const wchar_t *module_path = file_entry.path().c_str();
            HMODULE handle = LoadLibraryW(module_path);

            if (!handle) {
                DWORD error = GetLastError();

                std::string message;

                if (!error) {
                    get_logger().error("Failed to load mod {} but no error was produced.", file_entry.path().filename().string());
                } else {
                    message = get_error_message(error);
                }

                modloader::add_failed_mod({
                    file_entry.path(),
                    error,
                    message
                });

                SetLastError(0); // reset error for next time
                continue;
            }

            auto load = reinterpret_cast<load_func>(GetProcAddress(handle, "load"));

            if (!load) {
                DWORD error = GetLastError();
                std::string message = get_error_message(error);

                get_logger().error("Unable to get load() function in {}. Will not load.", file_entry.path().filename().string());
                get_logger().error("Error code: {:x}. {}", error, message);

                modloader::add_failed_mod({
                    file_entry.path(),
                    error,
                    message
                });

                continue;
            }

            mod_metadata metadata;
            load(&metadata);

            start_func start = reinterpret_cast<start_func>(GetProcAddress(handle, "start"));
            update_func update = reinterpret_cast<update_func>(GetProcAddress(handle, "update"));
            fixed_update_func fixed_update = reinterpret_cast<fixed_update_func>(GetProcAddress(handle, "fixed_update"));
            late_update_func late_update = reinterpret_cast<late_update_func>(GetProcAddress(handle, "late_update_func"));

            std::optional<start_func> start_opt = start ? std::optional<start_func>{start} : std::nullopt;
            std::optional<update_func> update_opt = update ? std::optional<update_func>{update} : std::nullopt;
            std::optional<fixed_update_func> fixed_update_opt = fixed_update ? std::optional<fixed_update_func>{fixed_update} : std::nullopt;
            std::optional<late_update_func> late_update_opt = late_update ? std::optional<late_update_func>{late_update} : std::nullopt;

            mod_info info {
                file_entry.path(),

                metadata,

                load,
                start_opt,
                update_opt,
                fixed_update_opt,
                late_update_opt,

                handle
            };

            modloader::add_loaded_mod(info);

            get_logger().info("------------------------------");
            get_logger().info("{} v{} ({})", metadata.name, metadata.version, metadata.id);
            get_logger().info("by {}", metadata.author);
            get_logger().info("Shared Object: {}", file_entry.path().filename().string());
            get_logger().info("------------------------------");
        }
    }

    std::vector<lib_info> modloader::loaded_libs;
    std::vector<mod_info> modloader::loaded_mods;
    std::vector<failed_lib> modloader::failed_libs;
    std::vector<failed_lib> modloader::failed_mods;

    bool modloader::get_mod_info(std::string mod_id, mod_info &info) {
        return false;
    }

    std::vector<lib_info> modloader::get_libs() {
        return modloader::loaded_libs;
    }

    std::vector<mod_info> modloader::get_mods() {
        return modloader::loaded_mods;
    }

    std::vector<failed_lib> modloader::get_failed_libs() {
        return modloader::failed_libs;
    }

    std::vector<failed_lib> modloader::get_failed_mods() {
        return modloader::failed_mods;
    }

    void modloader::add_loaded_lib(lib_info lib) {
        modloader::loaded_libs.push_back(lib);
    }

    void modloader::add_loaded_mod(mod_info mod) {
        modloader::loaded_mods.push_back(mod);
    }

    void modloader::add_failed_lib(failed_lib lib) {
        modloader::failed_libs.push_back(lib);
    }

    void modloader::add_failed_mod(failed_lib mod) {
        modloader::failed_mods.push_back(mod);
    }
}