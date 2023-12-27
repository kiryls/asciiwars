#include <stdio.h>
#include "include/raylib.h"

int main(int argc, char *argv[]) {

    char *window_title = "Ascii Wars";
    InitWindow(640, 480, window_title);
    char *text = "@";
    int font_size = 20;
    int font_space = 0;
    Vector2 text_pos = {10, 10};
    Font font = LoadFontEx("resources/FiraCodeNerdFont-Bold.ttf", font_size, 0, 255);

    SetTargetFPS(60);

    while (!WindowShouldClose()) { 
        if (IsKeyDown(KEY_D)) text_pos.x += 2.0f;
        if (IsKeyDown(KEY_A)) text_pos.x -= 2.0f;
        if (IsKeyDown(KEY_W)) text_pos.y -= 2.0f;
        if (IsKeyDown(KEY_S)) text_pos.y += 2.0f;

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTextEx(font, text, text_pos, font_size, font_space, RAYWHITE);
        EndDrawing();
    }

    return 0;
}
