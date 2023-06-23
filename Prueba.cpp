#include <raylib.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Prueba");

    Rectangle redSquare = { 100, 50, 200, 200 };
    Rectangle blueSquare = { 100, 450, 200, 200 };
    Color red = RED;
    Color blue = BLUE;

    bool isRedVisible = true;
    bool isBlueVisible = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            isRedVisible = true;
            isBlueVisible = false;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            isRedVisible = false;
            isBlueVisible = true;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (isRedVisible)
        {
            DrawRectangleRec(redSquare, red);
        }

        if (isBlueVisible)
        {
            DrawRectangleRec(blueSquare, blue);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
