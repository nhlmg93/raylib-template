#include <raylib.h>
#include <stdio.h>

void plugin_init(void) {
  InitWindow(800, 600, "Hot Reload");
  SetTargetFPS(60);
  printf("Plugin initialized\n");
}
void plugin_update(void) { printf("Plugin Update\n"); }

void plugin_render(void) {
  BeginDrawing();
  ClearBackground(BLACK);
  DrawCircle(500, 300, 50, RED);
  DrawText("TEST!", 100, 100, 20, WHITE);
  EndDrawing();
}
