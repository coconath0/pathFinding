#include <raylib.h>

void DrawRedSquare(Rectangle square)
{
    Color red = RED;
    DrawRectangleRec(square, red);
}

void DrawBlueSquare(Rectangle square)
{
    Color blue = BLUE;
    DrawRectangleRec(square, blue);
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Prueba");

    Rectangle redSquare = { 100, 50, 200, 200 };
    Rectangle blueSquare = { 100, 450, 200, 200 };

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
            DrawRedSquare(redSquare);
        }

        if (isBlueVisible)
        {
            DrawBlueSquare(blueSquare);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
