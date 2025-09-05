#include "plugin.h"
#include <dlfcn.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// FEATURE: handle multiple files from a directory (do i need to do this?)
// FEATURE: work with multiple directories(cmd, lib, build, assets, etc)
// FEATURE: better error handling(asserts!)

time_t get_time(const char *file) {
    struct stat st;
    return stat(file, &st) == 0 ? st.st_mtime : 0;
}

int main() {
    void *lib = NULL;
    plugin_init_func plugin_init = NULL;
    plugin_update_func plugin_update = NULL;
    plugin_render_func plugin_render = NULL;
    time_t last = 0;
    int frame = 0;

    // Allocate persistent game state
    GameState *game_state = calloc(1, sizeof(GameState));
    if (!game_state) {
        printf("Failed to allocate game state\n");
        return 1;
    }

    system("make -s plugin.so");
    lib = dlopen("./build/plugin.so", RTLD_LAZY);
    if (lib) {
        plugin_init = dlsym(lib, "plugin_init");
        plugin_update = dlsym(lib, "plugin_update");
        plugin_render = dlsym(lib, "plugin_render");
        if (plugin_init)
            plugin_init(game_state);
        last = get_time("plugin.c");
    }

    while (!WindowShouldClose()) {
        if (++frame % 30 == 0) {
            time_t now = get_time("plugin.c");
            if (now > last) {
                printf("Reloading plugin...\n");
                if (lib)
                    dlclose(lib);
                system("make -s plugin.so");
                lib = dlopen("./build/plugin.so", RTLD_LAZY);
                if (lib) {
                    plugin_update = dlsym(lib, "plugin_update");
                    plugin_render = dlsym(lib, "plugin_render");
                    printf("Plugin reloaded successfully\n");
                }
                last = now;
            }
        }

        if (plugin_update && plugin_render) {
            plugin_update(game_state);
            plugin_render(game_state);
        } else {
            BeginDrawing();
            ClearBackground(BLUE);
            DrawText("No plugin loaded", 10, 10, 20, WHITE);
            EndDrawing();
        }
    }

    if (lib)
        dlclose(lib);
    CloseWindow();
    free(game_state);
    return 0;
}
