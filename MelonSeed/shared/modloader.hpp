#pragma once

#include <filesystem>
#include <string>
#include <optional>
#include <vector>

#include <windows.h>

#ifdef MELON_SEED_EXPORT_SYMBOLS
#define MELON_SEED_EXPORT __declspec(dllexport)
#else
#define MELON_SEED_EXPORT
#endif

namespace melonseed {

    typedef struct {
        std::string id;
        std::string name;
        std::string version;
    } mod_metadata;

    using load_func = void (*)(mod_metadata *metadata);
    using start_func = void (*)();
    using update_func = void (*)();
    using fixed_update_func = void (*)();
    using late_update_func = void (*)();

    typedef struct {
        std::filesystem::path location;

        mod_metadata metadata;

        load_func load;
        std::optional<start_func> start;
        std::optional<update_func> update;
        std::optional<fixed_update_func> fixed_update;
        std::optional<late_update_func> late_update;

        HMODULE handle;
    } mod_info;

    typedef struct {
        std::filesystem::path location;
        DWORD error;
        std::string error_message;
    } failed_lib;

    typedef struct {
        std::filesystem::path location;
        HMODULE handle;
    } lib_info;

    class modloader {
    private:
        static std::vector<lib_info> loaded_libs;
        static std::vector<mod_info> loaded_mods;
        static std::vector<failed_lib> failed_libs;
        static std::vector<failed_lib> failed_mods;

    public:
        MELON_SEED_EXPORT static bool get_mod_info(std::string mod_id, mod_info &info);
        MELON_SEED_EXPORT static std::vector<lib_info> get_libs();
        MELON_SEED_EXPORT static std::vector<mod_info> get_mods();
        MELON_SEED_EXPORT static std::vector<failed_lib> get_failed_libs();
        MELON_SEED_EXPORT static std::vector<failed_lib> get_failed_mods();

        static void add_loaded_lib(lib_info lib);
        static void add_loaded_mod(mod_info mod);
        static void add_failed_lib(failed_lib lib);
        static void add_failed_mod(failed_lib mod);
    };

}