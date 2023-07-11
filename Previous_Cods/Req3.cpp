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

int originX = -1;
int originY = -1;
int destinationX = -1;
int destinationY = -1;

int editIndicatorSize = cellSize / 2;
int editIndicatorX = screenWidth - editIndicatorSize - 5;
int editIndicatorY = screenHeight - editIndicatorSize - 5;
bool showEditIndicator = false;

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

    if (showEditIndicator)
    {
        DrawRectangle(editIndicatorX, editIndicatorY, editIndicatorSize, editIndicatorSize, PURPLE);
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

        if (!editMode)
        {
            originX = -1;
            originY = -1;
            destinationX = -1;
            destinationY = -1;
        }

        if (editMode)
        {
            showEditIndicator = true;
        }
        else
        {
            showEditIndicator = false;
        }
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
    else
    {
        int mouseGridX = GetMouseX() / cellSize;
        int mouseGridY = GetMouseY() / cellSize;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (originX == -1 && originY == -1 && destinationX == -1 && destinationY == -1)
            {
                if (gridColors[mouseGridY][mouseGridX].r != 255 || gridColors[mouseGridY][mouseGridX].g != 0 || gridColors[mouseGridY][mouseGridX].b != 0)
                {
                    if (gridColors[mouseGridY][mouseGridX].r != 4 || gridColors[mouseGridY][mouseGridX].g != 255 || gridColors[mouseGridY][mouseGridX].b != 0)
                    {
                        // Si no se ha seleccionado origen, lo establecemos
                        originX = mouseGridX;
                        originY = mouseGridY;
                        gridColors[mouseGridY][mouseGridX] = GREEN;
                    }
                }
            }
            else if (originX != -1 && originY != -1 && destinationX != -1 && destinationY != -1)
            {
                // Si ya se seleccionaron origen y destino, evitamos seleccionar nuevamente
                return;
            }
            else if (originX != -1 && originY != -1 && (destinationX == -1 || destinationY == -1))
            {
                if (gridColors[mouseGridY][mouseGridX].r != 255 || gridColors[mouseGridY][mouseGridX].g != 0 || gridColors[mouseGridY][mouseGridX].b != 0)
                {
                    if (gridColors[mouseGridY][mouseGridX].r != 4 || gridColors[mouseGridY][mouseGridX].g != 255 || gridColors[mouseGridY][mouseGridX].b != 0)
                    {
                        // Si ya se seleccionó origen pero no destino, establecemos destino
                        destinationX = mouseGridX;
                        destinationY = mouseGridY;
                        gridColors[mouseGridY][mouseGridX] = YELLOW;
                    }
                }
            }
        }
    }
}

int main()
{
    InitWindow(screenWidth, screenHeight, "Pathfinding App");
    SetTargetFPS(60);

    gridSizeX = screenWidth / cellSize;
    gridSizeY = screenHeight / cellSize;

    InitializeGrid();

    while (!WindowShouldClose())
    {
        // Update
        ToggleEditMode();
        UpdateGrid();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawGrid();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
