#include <raylib.h>

typedef struct {
  int foo_t;
} GameState;

typedef void (*plugin_init_func)(GameState* state);
typedef void (*plugin_update_func)(GameState* state);
typedef void (*plugin_render_func)(GameState* state);
