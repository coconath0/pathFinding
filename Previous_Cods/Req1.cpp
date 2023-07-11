
#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 800;
const int cellSize = 20;

int numCellsX;
int numCellsY;

void DrawGrid(){
    for (int y = 0; y < numCellsY; y++){
        for (int x = 0; x < numCellsX; x++){
            Color cellColor = { 184, 237, 255, 255 }; // Color celeste claro (#b8edff)
            DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, cellColor);
            DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, DARKBLUE);
        }
    }
}

int main(){
    numCellsX = screenWidth / cellSize;
    numCellsY = screenHeight / cellSize;

    InitWindow(screenWidth, screenHeight, "Pathfinding");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawGrid();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
