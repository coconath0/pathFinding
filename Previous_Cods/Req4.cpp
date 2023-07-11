#include <raylib.h>
#include <queue>
#include <climits>

const int screenWidth = 800;
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

int distanceMap[100][100];

/* bool pathCalculating = false; */

void InitializeGrid()
{

    // Inicializar el mapa de distancias
    for (int y = 0; y < gridSizeY; y++)
    {
        for (int x = 0; x < gridSizeX; x++)
        {
            gridColors[y][x] = { 184, 237, 255, 255 };
            distanceMap[y][x] = (gridColors[y][x].r == 255 && gridColors[y][x].g == 0 && gridColors[y][x].b == 0) ? INT_MAX : 0;
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

        showEditIndicator = editMode;
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
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                gridColors[mouseGridY][mouseGridX] = RED;
            }
            else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                if (ColorToInt(gridColors[mouseGridY][mouseGridX]) != ColorToInt(RED))
                {
                    gridColors[mouseGridY][mouseGridX] = { 184, 237, 255, 255 }; //celeste
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

        // Verificar si se ha presionado la tecla Enter
        if (IsKeyPressed(KEY_ENTER))
        {
            if (originX != -1 && originY != -1 && destinationX != -1 && destinationY != -1)
            {
                std::queue<std::pair<int, int>> q;
                int distanceMap[100][100];

                // Inicializar el mapa de distancias
                for (int y = 0; y < gridSizeY; y++)
                {
                    for (int x = 0; x < gridSizeX; x++)
                    {
                        distanceMap[y][x] = INT_MAX;
                    }
                }

                // Establecer la distancia del origen a 0
                distanceMap[originY][originX] = 0;

                // Agregar el origen a la cola
                q.push(std::make_pair(originX, originY));

                // Algoritmo de búsqueda de ruta utilizando lista 1
                while (!q.empty())
                {
                    std::pair<int, int> current = q.front();
                    int x = current.first;
                    int y = current.second;
                    q.pop();

                    // Verificar si la casilla actual es roja
                    if (gridColors[y][x].r == 230 && gridColors[y][x].g == 41 && gridColors[y][x].b == 55)  {
                        continue; // Saltar a la siguiente iteración sin expandir los vecinos
                    }

                    // Verificar casillas adyacentes
                    if (x > 0 && distanceMap[y][x - 1] == INT_MAX)
                    {
                        if (gridColors[y][x - 1].r != 230 || gridColors[y][x - 1].g != 41 || gridColors[y][x - 1].b != 55)
                        {
                            distanceMap[y][x - 1] = distanceMap[y][x] + 1;
                            q.push(std::make_pair(x - 1, y));
                        }
                    }
                    if (x < gridSizeX - 1 && distanceMap[y][x + 1] == INT_MAX)
                    {
                        if (gridColors[y][x + 1].r != 230 || gridColors[y][x + 1].g != 41 || gridColors[y][x + 1].b != 55)
                        {
                            distanceMap[y][x + 1] = distanceMap[y][x] + 1;
                            q.push(std::make_pair(x + 1, y));
                        }
                    }
                    if (y > 0 && distanceMap[y - 1][x] == INT_MAX)
                    {
                        if (gridColors[y - 1][x].r != 230 || gridColors[y - 1][x].g != 41 || gridColors[y - 1][x].b != 55)
                        {
                            distanceMap[y - 1][x] = distanceMap[y][x] + 1;
                            q.push(std::make_pair(x, y - 1));
                        }
                    }
                    if (y < gridSizeY - 1 && distanceMap[y + 1][x] == INT_MAX)
                    {
                        if (gridColors[y + 1][x].r != 230 || gridColors[y + 1][x].g != 41 || gridColors[y + 1][x].b != 55)
                        {
                            distanceMap[y + 1][x] = distanceMap[y][x] + 1;
                            q.push(std::make_pair(x, y + 1));
                        }
                    }


                }

                // Pintar la ruta con color azul (#0000ff)
                int x = destinationX;
                int y = destinationY;
                while (x != originX || y != originY)
                {
                    int currentDistance = distanceMap[y][x];

                    if (x > 0 && distanceMap[y][x - 1] == currentDistance - 1)
                    {
                        x--;
                    }
                    else if (x < gridSizeX - 1 && distanceMap[y][x + 1] == currentDistance - 1)
                    {
                        x++;
                    }
                    else if (y > 0 && distanceMap[y - 1][x] == currentDistance - 1)
                    {
                        y--;
                    }
                    else if (y < gridSizeY - 1 && distanceMap[y + 1][x] == currentDistance - 1)
                    {
                        y++;
                    }

                    if (x != originX || y != originY)
                    {
                        gridColors[y][x] = BLUE;
                    }
                    //gridColors[y][x] = BLUE;
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