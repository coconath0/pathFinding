#include <raylib.h>
#include <queue>
#include <climits>
#include <cmath>
#include <chrono>
#include <iostream>

struct Node
{
    int x;
    int y;
    Node* next;
};

class LinkedList
{
private:
    Node* head;
    Node* tail;

public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void Append(int x, int y)
    {
        Node* newNode = new Node;
        newNode->x = x;
        newNode->y = y;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    bool IsEmpty()
    {
        return head == nullptr;
    }

    void RemoveHead()
    {
        if (head == nullptr)
            return;

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    int GetHeadX()
    {
        if (head != nullptr)
            return head->x;

        return -1;
    }

    int GetHeadY()
    {
        if (head != nullptr)
            return head->y;

        return -1;
    }
};

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

void InitializeGrid()
{
    for (int y = 0; y < gridSizeY; y++)
    {
        for (int x = 0; x < gridSizeX; x++)
        {
            gridColors[y][x] = {184, 237, 255, 255};
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

void ClearNonTargetCells()
{
    for (int y = 0; y < gridSizeY; y++)
    {
        for (int x = 0; x < gridSizeX; x++)
        {
            if (!((gridColors[y][x].r == 230 && gridColors[y][x].g == 41 && gridColors[y][x].b == 55) ||
                  (gridColors[y][x].r == 0 && gridColors[y][x].g == 228 && gridColors[y][x].b == 48) ||
                  (gridColors[y][x].r == 253 && gridColors[y][x].g == 249 && gridColors[y][x].b == 0)))
            {
                gridColors[y][x] = {184, 237, 255, 255}; 
            }
        }
    }
}

void Dijkstra() 
{
    ClearNonTargetCells();

    LinkedList queue;
    int distanceMap[100][100];

    for (int y = 0; y < gridSizeY; y++)
    {
        for (int x = 0; x < gridSizeX; x++)
        {
            distanceMap[y][x] = INT_MAX;
        }
    }

    distanceMap[originY][originX] = 0;

    queue.Append(originX, originY);

    while (!queue.IsEmpty())
    {
        int x = queue.GetHeadX();
        int y = queue.GetHeadY();
        queue.RemoveHead();

        if (gridColors[y][x].r == 230 && gridColors[y][x].g == 41 && gridColors[y][x].b == 55)
        {
            continue; 
        }
        
        if (x > 0 && distanceMap[y][x - 1] == INT_MAX)
        {
            if (gridColors[y][x - 1].r != 230 || gridColors[y][x - 1].g != 41 || gridColors[y][x - 1].b != 55)
            {
                distanceMap[y][x - 1] = distanceMap[y][x] + 1;
                queue.Append(x - 1, y);
            }
        }
        if (x < gridSizeX - 1 && distanceMap[y][x + 1] == INT_MAX)
        {
            if (gridColors[y][x + 1].r != 230 || gridColors[y][x + 1].g != 41 || gridColors[y][x + 1].b != 55)
            {
                distanceMap[y][x + 1] = distanceMap[y][x] + 1;
                queue.Append(x + 1, y);
            }
        }
        if (y > 0 && distanceMap[y - 1][x] == INT_MAX)
        {
            if (gridColors[y - 1][x].r != 230 || gridColors[y - 1][x].g != 41 || gridColors[y - 1][x].b != 55)
            {
                distanceMap[y - 1][x] = distanceMap[y][x] + 1;
                queue.Append(x, y - 1);
            }
        }
        if (y < gridSizeY - 1 && distanceMap[y + 1][x] == INT_MAX)
        {
            if (gridColors[y + 1][x].r != 230 || gridColors[y + 1][x].g != 41 || gridColors[y + 1][x].b != 55)
            {
                distanceMap[y + 1][x] = distanceMap[y][x] + 1;
                queue.Append(x, y + 1);
            }
        }
    }

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
    }
}

void FocussedD() 
{
    ClearNonTargetCells();

    std::priority_queue<std::pair<int, std::pair<int, int>>> q;
    int distanceMap[100][100];

    for (int y = 0; y < gridSizeY; y++)
    {
        for (int x = 0; x < gridSizeX; x++)
        {
            distanceMap[y][x] = INT_MAX;
        }
    }

    distanceMap[originY][originX] = 0;

    q.push(std::make_pair(0, std::make_pair(originX, originY)));

    while (!q.empty())
    {
        std::pair<int, std::pair<int, int>> current = q.top();
        int x = current.second.first;
        int y = current.second.second;
        q.pop();

        if (gridColors[y][x].r == 230 && gridColors[y][x].g == 41 && gridColors[y][x].b == 55)
        {
            continue; 
        }

        if (x == destinationX && y == destinationY)
        {
            break;
        }

        if (x > 0 && distanceMap[y][x - 1] == INT_MAX)
        {
            if (gridColors[y][x - 1].r != 230 || gridColors[y][x - 1].g != 41 || gridColors[y][x - 1].b != 55)
            {
                int g = distanceMap[y][x] + 1;
                int h = abs(destinationX - (x - 1)) + abs(destinationY - y);
                int newF = g + h;

                distanceMap[y][x - 1] = g;
                q.push(std::make_pair(newF, std::make_pair(x - 1, y)));
            }
        }
        if (x < gridSizeX - 1 && distanceMap[y][x + 1] == INT_MAX)
        {
            if (gridColors[y][x + 1].r != 230 || gridColors[y][x + 1].g != 41 || gridColors[y][x + 1].b != 55)
            {
                int g = distanceMap[y][x] + 1;
                int h = abs(destinationX - (x + 1)) + abs(destinationY - y);
                int newF = g + h;

                distanceMap[y][x + 1] = g;
                q.push(std::make_pair(newF, std::make_pair(x + 1, y)));
            }
        }
        if (y > 0 && distanceMap[y - 1][x] == INT_MAX)
        {
            if (gridColors[y - 1][x].r != 230 || gridColors[y - 1][x].g != 41 || gridColors[y - 1][x].b != 55)
            {
                int g = distanceMap[y][x] + 1;
                int h = abs(destinationX - x) + abs(destinationY - (y - 1));
                int newF = g + h;

                distanceMap[y - 1][x] = g;
                q.push(std::make_pair(newF, std::make_pair(x, y - 1)));
            }
        }
        if (y < gridSizeY - 1 && distanceMap[y + 1][x] == INT_MAX)
        {
            if (gridColors[y + 1][x].r != 230 || gridColors[y + 1][x].g != 41 || gridColors[y + 1][x].b != 55)
            {
                int g = distanceMap[y][x] + 1;
                int h = abs(destinationX - x) + abs(destinationY - (y + 1));
                int newF = g + h;

                distanceMap[y + 1][x] = g;
                q.push(std::make_pair(newF, std::make_pair(x, y + 1)));
            }
        }
    }

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
            gridColors[y][x] = PURPLE;
        }
    }
}

int CountGridsColor1()
{
    int count = 0;

    for (int y = 0; y < gridSizeY; y++)
    {
        for (int x = 0; x < gridSizeX; x++)
        {
            if (gridColors[y][x].r == 0 && gridColors[y][x].g == 121 && gridColors[y][x].b == 241 && gridColors[y][x].a == 255)
            {
                count++;
            }
        }
    }

    return count;
}

int CountGridsColor2()
{
    int count = 0;

    for (int y = 0; y < gridSizeY; y++)
    {
        for (int x = 0; x < gridSizeX; x++)
        {
            if (gridColors[y][x].r == 200 && gridColors[y][x].g == 122 && gridColors[y][x].b == 255 && gridColors[y][x].a == 255)
            {
                count++;
            }
        }
    }

    return count;
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
            else if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON))
            {
                if (gridColors[mouseGridY][mouseGridX].r != 255 || gridColors[mouseGridY][mouseGridX].g != 0 || gridColors[mouseGridY][mouseGridX].b != 0)
                {
                    gridColors[mouseGridY][mouseGridX] = {184, 237, 255, 255}; 
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
                        originX = mouseGridX;
                        originY = mouseGridY;
                        gridColors[mouseGridY][mouseGridX] = GREEN;
                    }
                }
            }
            else if (originX != -1 && originY != -1 && destinationX != -1 && destinationY != -1)
            {
                return;
            }
            else if (originX != -1 && originY != -1 && (destinationX == -1 || destinationY == -1))
            {
                if (gridColors[mouseGridY][mouseGridX].r != 255 || gridColors[mouseGridY][mouseGridX].g != 0 || gridColors[mouseGridY][mouseGridX].b != 0)
                {
                    if (gridColors[mouseGridY][mouseGridX].r != 4 || gridColors[mouseGridY][mouseGridX].g != 255 || gridColors[mouseGridY][mouseGridX].b != 0)
                    {
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

    bool restart = false;

    while (!restart)
    {
        ToggleEditMode();
        UpdateGrid();

        if (IsKeyPressed(KEY_ENTER))
        {
            auto startTime = std::chrono::high_resolution_clock::now();
            Dijkstra();
            int countColor1 = CountGridsColor1(); 
            std::cout << "\033[1;36mCantidad de celdas pintadas del color del algoritmo 1: " << countColor1 << "\033[0m" << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            std::cout << "\033[1;36mTiempo de ejecucion de Dijkstra: " << duration << " microsegundos\033[0m" << std::endl;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            auto startTime = std::chrono::high_resolution_clock::now();
            FocussedD();
            int countColor2 = CountGridsColor2();
            std::cout << "\033[1;35mCantidad de celdas pintadas del color del algoritmo 2: " << countColor2 << "\033[0m" << std::endl; // Obtener recuento de grids de color 2
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
            std::cout << "\033[1;35mTiempo de ejecucion de FocussedD: " << duration << " microsegundos\033[0m" << std::endl;
        }

        BeginDrawing();
        DrawGrid();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            InitializeGrid();
            originX = -1;
            originY = -1;
            destinationX = -1;
            destinationY = -1;
            editMode = false;
            showEditIndicator = false;
        }

        if (IsKeyPressed(KEY_LEFT_SHIFT))
        {
            CloseWindow();
        }

        EndDrawing();
    }
    return 0;
}