#include "main.hpp"
#include "files.hpp"
#include "logger.hpp"

#include <windows.h>
#include <format>

#include "dobby.h"

#include "il2cpp-api.h"
#include "il2cpp-class-internals.h"

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

            std::exit(EXIT_FAILURE);
        }
    }
}

MELON_SEED_ENTRYPOINT void melon_seed_init() {
    create_directories();

    // initialise logger
    melonseed::logger::initialise_logger();
    get_logger().info("Logger initialised.");

    // open libraries

    // open mods
    // construct mods
    // load mods
}

MELON_SEED_ENTRYPOINT void melon_seed_start() {
    // start mods
    // ???
    // profit
}