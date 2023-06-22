#include <raylib.h>

const int screenWidth = 1000;
const int screenHeight = 800;
const int cellSize = 20;

int gridSizeX;
int gridSizeY;

Color gridColors[100][100];
bool editMode = false;
bool ctrlPressed = false;
bool mousePressed = false;

void InitializeGrid()
{
    for (int y = 0; y < gridSizeY; y++)
    {
        for (int x = 0; x < gridSizeX; x++)
        {
            gridColors[y][x] = { 184, 237, 255, 255 };
        }
    }
}

void DrawGrid()
{
    for (int y = 0; y < gridSizeY; y++)
    {
        for (int x = 0; x < gridSizeX; x++)
        {
            DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, gridColors[y][x]);
            DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, DARKBLUE);
        }
    }
}

void ToggleEditMode()
{
    if (IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_RIGHT_CONTROL))
    {
        ctrlPressed = true;
    }
    else if (ctrlPressed && !IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_RIGHT_CONTROL))
    {
        ctrlPressed = false;
        editMode = !editMode;
    }
}

void UpdateGrid()
{
    if (editMode)
    {
        int mouseGridX = GetMouseX() / cellSize;
        int mouseGridY = GetMouseY() / cellSize;

        if (mouseGridX >= 0 && mouseGridX < gridSizeX && mouseGridY >= 0 && mouseGridY < gridSizeY)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                gridColors[mouseGridY][mouseGridX] = RED;
            }
            else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            {
                if (ColorToInt(gridColors[mouseGridY][mouseGridX]) == ColorToInt(RED))
                {
                    gridColors[mouseGridY][mouseGridX] = { 184, 237, 255, 255 };
                }
            }
        }
    }
}

int main()
{
    gridSizeX = screenWidth / cellSize;
    gridSizeY = screenHeight / cellSize;

    InitializeGrid();

    InitWindow(screenWidth, screenHeight, "Pathfinding");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        ToggleEditMode();
        UpdateGrid();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawGrid();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
