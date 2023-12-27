#include <stdio.h>
#include "include/raylib.h"
#include "include/raymath.h"

int main(int argc, char *argv[]) {

    char *window_title = "Ascii Wars";
    InitWindow(640, 480, window_title);
    char *text = "@";
    int font_size = 20;
    int font_space = 0;
    Vector2 text_pos = {10, 10};
    Font font = LoadFontEx("resources/FiraCodeNerdFont-Bold.ttf", font_size, 0, 255);

    SetTargetFPS(60);

    Vector2 dir = {0};
    while (!WindowShouldClose()) { 
        if (IsKeyDown(KEY_D)) dir.x += 1.0f;
        if (IsKeyDown(KEY_A)) dir.x -= 1.0f;
        if (IsKeyDown(KEY_W)) dir.y -= 1.0f;
        if (IsKeyDown(KEY_S)) dir.y += 1.0f;

        dir = Vector2Normalize(dir);

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTextEx(font, text, dir, font_size, font_space, RAYWHITE);
        EndDrawing();
    }

    return 0;
}
