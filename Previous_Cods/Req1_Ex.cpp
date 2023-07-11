#include <raylib.h> // Incluir la biblioteca Raylib

const int screenWidth = 1000; // Ancho de la ventana
const int screenHeight = 800; // Alto de la ventana
const int cellSize = 20; // Tamaño de cada celda en la cuadrícula

int numCellsX; // Número de celdas en el eje X
int numCellsY; // Número de celdas en el eje Y

void DrawGrid(){
    for (int y = 0; y < numCellsY; y++){ // Bucle para recorrer las filas de la cuadrícula
        for (int x = 0; x < numCellsX; x++){ // Bucle para recorrer las columnas de la cuadrícula
            Color cellColor = { 184, 237, 255, 255 }; // Color celeste claro (#b8edff)
            
            // Dibujar un rectángulo relleno para representar una celda en la posición (x, y)
            DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, cellColor);
            
            // Dibujar un rectángulo sin relleno para representar el borde de la celda en la posición (x, y)
            DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, DARKBLUE);
        }
    }
}

int main(){
    numCellsX = screenWidth / cellSize; // Calcular el número de celdas en el eje X
    numCellsY = screenHeight / cellSize; // Calcular el número de celdas en el eje Y

    // Inicializar la ventana con el ancho, alto y título especificados
    InitWindow(screenWidth, screenHeight, "Pathfinding");

    // Establecer la velocidad de actualización de la ventana en 60 cuadros por segundo
    SetTargetFPS(60);

    while (!WindowShouldClose()){ // Bucle principal que se ejecuta mientras la ventana no se cierre
        BeginDrawing(); // Iniciar el proceso de dibujo en la ventana

        // Borrar el fondo de la ventana con color blanco
        ClearBackground(RAYWHITE);

        // Dibujar la cuadrícula en la ventana
        DrawGrid();

        EndDrawing(); // Finalizar el proceso de dibujo en la ventana
    }

    // Cerrar la ventana y liberar los recursos utilizados
    CloseWindow();

    return 0;
}
