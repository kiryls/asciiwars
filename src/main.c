#include <math.h>
#include <stdbool.h>

#include "include/raylib.h"
#include "include/raymath.h"

#define SCREEN_W 640
#define SCREEN_H 480
#define CELL_SIZE 20
#define ROWS (SCREEN_H / CELL_SIZE)
#define COLS (SCREEN_W / CELL_SIZE)

#define COLORS(C) (GetColor(colors[(C)]))

typedef enum {
    COLOR_BG = 0,
    COLOR_TEXT,
    COLOR_GRID,
    COLOR_I_ARCHER,
    COLOR_I_LIGHT,
    COLOR_I_HEAVY,
    COLOR_C_KNIGHT,
    COLOR_C_CHARIOT,
    COLOR_A_CATAPULT,
    COLOR_A_SIEGE_TOWER
} Colors;

unsigned int colors[] = {
    [COLOR_BG] = 0X222222FF,
    [COLOR_TEXT] = 0xAAAAAAFF,
    [COLOR_GRID] = 0x333333FF
};

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

void DrawCells() {
    for(int i = 0; i < ROWS; ++i) {
        DrawLine(0, i * CELL_SIZE, SCREEN_W, i * CELL_SIZE, COLORS(COLOR_GRID));
    }

    for(int i = 0; i < COLS; ++i) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_H, COLORS(COLOR_GRID));
    }
}

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
    int font_size = CELL_SIZE - 2;
    int font_space = 0;
    float speed = 4;
    Font font = LoadFontEx("resources/FiraCodeNerdFont-Bold.ttf", font_size, 0, 255);
    Color friend = SKYBLUE;
    Color foe = ORANGE;
    Vector2 text_pos = {5, 1};

    Unit unit = {.type = U_ARTILLERY, .role.artillery = A_SIEGE_TOWER};

    SetTargetFPS(60);

    Vector2 dir = {0};
    Vector2 xy;
    Vector2 fontCharSize;
    while (!WindowShouldClose()) { 
        if (IsKeyDown(KEY_D)) dir.x += 1.0f;
        if (IsKeyDown(KEY_A)) dir.x -= 1.0f;
        if (IsKeyDown(KEY_W)) dir.y -= 1.0f;
        if (IsKeyDown(KEY_S)) dir.y += 1.0f;

        // update text_pos

        dir = Vector2Normalize(dir);

        text_pos = Vector2Add(text_pos, Vector2Scale(dir, CELL_SIZE));

        dir = Vector2Zero();

        BeginDrawing();
        ClearBackground(COLORS(COLOR_BG));
        
        DrawCells();
        fontCharSize = MeasureTextEx(font, "@", font_size, font_space);
        xy.x = floor(text_pos.x/CELL_SIZE) * CELL_SIZE + (CELL_SIZE - fontCharSize.x)/2; 
        xy.y = floor(text_pos.y/CELL_SIZE) * CELL_SIZE + (CELL_SIZE - fontCharSize.y)/2; 
        DrawTextEx(font, GetAvatar(unit), xy, font_size, font_space, COLORS(COLOR_TEXT));
        EndDrawing();
    }

    return 0;
}
