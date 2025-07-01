#include <dlfcn.h>
#include <raylib.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef void (*plugin_func)(void);

time_t get_time(const char *file) {
  struct stat st;
  return stat(file, &st) == 0 ? st.st_mtime : 0;
}

int main() {
  void *lib = NULL;
  plugin_func plugin_init = NULL;
  plugin_func plugin_update = NULL;
  plugin_func plugin_render = NULL;
  time_t last = 0;
  int frame = 0;

  system("make -s plugin.so");
  lib = dlopen("./plugin.so", RTLD_LAZY);
  if (lib) {
    plugin_init = dlsym(lib, "plugin_init");
    plugin_update = dlsym(lib, "plugin_update");
    plugin_render = dlsym(lib, "plugin_render");
    if (plugin_init)
      plugin_init();
    last = get_time("plugin.c");
  }

  while (!WindowShouldClose()) {
    if (++frame % 30 == 0) {
      time_t now = get_time("plugin.c");
      if (now > last) {
        if (lib)
          dlclose(lib);
        system("make -s plugin.so");
        lib = dlopen("./plugin.so", RTLD_LAZY);
        if (lib) {
          plugin_update = dlsym(lib, "plugin_update");
          plugin_render = dlsym(lib, "plugin_render");
        }
        last = now;
      }
    }

    if (plugin_update && plugin_render) {
      plugin_update();
      plugin_render();
    } else {
      BeginDrawing();
      ClearBackground(BLUE);
      DrawText("No plugin", 10, 10, 20, WHITE);
      EndDrawing();
    }
  }

  if (lib)
    dlclose(lib);
  CloseWindow();
  return 0;
}
