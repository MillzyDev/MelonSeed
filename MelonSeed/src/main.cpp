#define MELON_SEED_ENTRYPOINT extern "C" __declspec(dllexport)

MELON_SEED_ENTRYPOINT void melon_seed_init() {
    // initialise logger

    // install other hooks (Scene loaded or smth, just some callbacks more or less)

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