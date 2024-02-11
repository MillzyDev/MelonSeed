#include "MelonSeed/shared/modloader.hpp"
#include "MelonSeed/shared/logger.hpp"

melonseed::logger logger("TestMod");

MELON_SEED_API void load(melonseed::mod_metadata *data) {
    *data = {
        "dev.Millzy.TestMod",
        "TestMod",
        "0.1.0",
        "Millzy"
    };

    logger.info("Hello world!");
}
