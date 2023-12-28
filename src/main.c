#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/raylib.h"
#include "include/raymath.h"

#define SCREEN_W 640
#define SCREEN_H 480
#define CELL_SIZE 20
#define ROWS (SCREEN_H / CELL_SIZE)
#define COLS (SCREEN_W / CELL_SIZE)


typedef enum {
    I_ARCHER = 0,
    I_LIGHT,
    I_HEAVY
} Infantry;

typedef enum {
    C_KNIGHT = 3,
    C_CHARIOT
} Cavalry;

typedef enum {
    A_CATAPULT = 5,
    A_SIEGE_TOWER
} Artillery;

typedef enum {
    U_INFANTRY,
    U_CAVALRY,
    U_ARTILLERY
} UnitType;

typedef struct {
    UnitType type;
    union {
        Infantry infantry;
        Cavalry cavalry;
        Artillery artillery;
    } role;
} Unit;

static char* avatar[] = {
    [I_LIGHT]       = "l",
    [I_HEAVY]       = "h",
    [I_ARCHER]      = ")",
    [C_KNIGHT]      = "k",
    [C_CHARIOT]     = "%",
    [A_CATAPULT]    = "*",
    [A_SIEGE_TOWER] = "#"
};

char *GetAvatar(Unit unit) {
    switch (unit.type) {
        case U_INFANTRY: 
            return avatar[unit.role.infantry];
        case U_CAVALRY: 
            return avatar[unit.role.cavalry];
        case U_ARTILLERY: 
            return avatar[unit.role.artillery];
    }
}

int main(int argc, char *argv[]) {

    char *window_title = "Ascii Wars";
    InitWindow(SCREEN_W, SCREEN_H, window_title);
    int font_size = 20;
    int font_space = 0;
    Vector2 text_pos = {10, 10};
    float speed = 4;
    Font font = LoadFontEx("resources/FiraCodeNerdFont-Bold.ttf", font_size, 0, 255);
    Color friend = SKYBLUE;
    Color foe = ORANGE;

    Unit unit = {.type = U_INFANTRY, .role = I_ARCHER};

    SetTargetFPS(60);

    Vector2 dir = {0};
    while (!WindowShouldClose()) { 
        if (IsKeyDown(KEY_D)) dir.x += 1.0f;
        if (IsKeyDown(KEY_A)) dir.x -= 1.0f;
        if (IsKeyDown(KEY_W)) dir.y -= 1.0f;
        if (IsKeyDown(KEY_S)) dir.y += 1.0f;

        dir = Vector2Normalize(dir);

        text_pos = Vector2Add(text_pos, Vector2Scale(dir, speed));

        dir = Vector2Zero();

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawTextEx(font, GetAvatar(unit), text_pos, font_size, font_space, foe);
        EndDrawing();
    }

    return 0;
}
