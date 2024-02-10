#include "main.hpp"
#include "files.hpp"
#include "logger.hpp"
#include "modloader_internal.hpp"

#include <windows.h>
#include <format>

#include "dobby.h"

#include "il2cpp-api.h"
#include "il2cpp-class-internals.h"
#include "il2cpp-object-internals.h"

#define MELON_SEED_ENTRYPOINT extern "C" __declspec(dllexport)

melonseed::logger get_logger() {
    static melonseed::logger logger("MelonSeed");
    return logger;
}

void create_directories() {
    std::filesystem::path directories[] = {
            melonseed::files::get_logs_dir(),
            melonseed::files::get_mods_dir(),
            melonseed::files::get_libs_dir()
    };

    for (auto directory : directories) {
        if (exists(directory))
            continue;

        std::error_code error;
        bool success = std::filesystem::create_directories(directory, error);

        if (!success) {
            (void)MessageBoxA(
                    nullptr,
                    std::format(
                            "Failed to create essential directories.\n"
                            "Error Code: {0:x}\n"
                            "Message: {1}.",

                            error.value(),
                            error.message()).c_str(),
                    "MelonSeed - Fatal Error",
                    MB_ICONERROR | MB_OK);

            std::abort();
        }
    }
}

MELON_SEED_ENTRYPOINT void melon_seed_init() {
    create_directories();

    melonseed::logger::initialise_logger();
    get_logger().info("Logger initialised.");

    get_logger().info("");
    get_logger().info("------------------------------");
    get_logger().info("MelonSeed v0.1.0");
    get_logger().info("by Millzy");
    get_logger().info("------------------------------");
    get_logger().info("");

    melonseed::open_libs(melonseed::files::get_libs_dir());

    melonseed::open_mods(melonseed::files::get_mods_dir());
}

MELON_SEED_ENTRYPOINT void melon_seed_start() {
    // hook callbacks

    // start mods
    // ???
    // profit
}