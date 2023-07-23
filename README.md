# Pathfinding Algorithms Visualization in C++
This project aims to implement a graphical application in C++ or Haskell that allows you to explore and compare various pathfinding algorithms. Pathfinding is a critical aspect of artificial intelligence, especially in video games. It involves finding the most efficient route for an object (e.g., a game character) to reach a target position while avoiding obstacles.

## Algorithms Included
The application will showcase the following pathfinding algorithms:

### List A
- Breadth-First-Search
- Dijkstra's Algorithm
- A* (A star)

### List B
- D* Algorithm
- Focused D* Algorithm
- D* Lite Algorithm

## Requirements

### 1. Grid Display
The application will display a grid on the screen. The number of grid cells should adjust based on the width and height of the screen. Each cell of the grid will be represented by a light blue color (#b8edff).

### 2. Editing Mode (CTRL Key)
By pressing the CTRL key, the application will enter the editing mode. In this mode, the user can perform the following actions:

- Left-clicking on a cell will block it (unavailable for pathfinding), and the cell should turn red (#ff0000).
- Right-clicking on a blocked cell will unblock it (available for pathfinding). If the cell is currently blocked (red), it should return to the light blue color. If the cell is already unblocked, nothing will happen.
- Pressing CTRL again will exit the editing mode.

### 3. Selecting Origin and Destination
Outside of the editing mode, the application will allow the user to select an origin and destination cell using the mouse (left-click). The selected origin cell should be colored green (#04ff00), and the destination cell should be colored yellow (#ffea00).

### 4. Displaying Route (Algorithm 1)
After selecting the origin and destination cells, pressing the ENTER key will trigger the pathfinding algorithm from List A. The application will paint the route between the origin and destination cells with blue color (#0000ff).

### 5. Displaying Route (Algorithm 2)
After selecting the origin and destination cells, pressing the SPACE key will trigger the pathfinding algorithm from List B. The application will paint the route between the origin and destination cells with blue color (#0000ff).

### 6. Resetting the Grid (ESC Key)
Pressing the ESC key will reset the application to its initial state, with all cells unblocked and colored light blue.

## Libraries Used
To simplify the development of the graphical application, we utilized the "raylib" library, developed by Ramon Santamaria. Raylib facilitates graphic application development in the C programming language. Although it is a C-based library, it can also be easily used in C++ applications, and there are ports available for various programming languages.

### Installation
Please refer to the official Raylib website (https://www.raylib.com/) for instructions on how to install the library.

## Build and Run
We have provided a Makefile to make compiling and running the C++ code easier. Follow these steps to build and run the application:

1. Open a terminal and navigate to the project directory.
2. Run the command `make` to compile the C++ code.
3. After successful compilation, execute the application using the generated executable.
4. Follow the on-screen instructions to interact with the application and visualize the pathfinding algorithms.

If you are not familiar with using the Makefile, you can refer to this helpful tutorial (https://www.youtube.com/watch?v=taCJhnBXG_w) that we used as a reference to create the Makefile and simplify the build process.

## Getting Started
To get started, clone this repository and follow the instructions provided in the project documentation. Implement your preferred pathfinding algorithms using the Raylib library in either C++ or Haskell and see how they perform in the graphical application.

## Credits
This project is part of the final assignment for the pathfinding algorithms course. Credits to the course instructor and contributors for the educational content and inspiration for this project.

## License
This project is licensed under the [MIT License](LICENSE). Feel free to use and modify it as per the terms of the license.