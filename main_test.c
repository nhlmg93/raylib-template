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
  time_t last = 0;
  int frame = 0;

  system("make -s tests");
  last = get_time("tests.out");

  while (true) {
    time_t now = get_time("test_plugin.c");
    if (now > last) {
      system("make -s tests");
      last = now;
    }
  }

  return 0;
}
