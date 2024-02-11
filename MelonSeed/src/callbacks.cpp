#include "callbacks.hpp"
#include "modloader.hpp"
#include "main.hpp"

#include "il2cpp-api.h"
#include "il2cpp-class-internals.h"
#include "dobby.h"

namespace melonseed::callbacks {
    void register_callbacks() {
        std::vector<mod_info> mod_infos = modloader::get_mods();
        for (mod_info mod : mod_infos) {
            // TODO
        }
    }

    void install_callback_hooks() {
        // TODO
    }
}