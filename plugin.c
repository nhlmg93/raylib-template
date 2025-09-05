#include "plugin.h"
#include <raylib.h>
#include <stdio.h>

void plugin_init(GameState *state) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(1200, 800, "Hot Reload");
  SetTargetFPS(60);

  // Initialize game state
  state->foo_t = 500;

  printf("Plugin initialized\n");
}

void plugin_update(GameState *state) {
  printf("Plugin test- Score: %d\n", state->foo_t);
}

void plugin_render(GameState *state) {
  BeginDrawing();
  ClearBackground(BLACK);


  DrawText("We are working", 10, 10, 20, WHITE);

  EndDrawing();
}
