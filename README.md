# Pathfinding Visualizer (SFML 3.0)

An interactive pathfinding algorithm visualizer built with C++17 and SFML 3.0. This project allows users to observe classical Graph Theory algorithms in real-time on a dynamic grid.

## Features
* **Implemented Algorithms:** BFS (Breadth-First Search), DFS (Depth-First Search), Dijkstra and A*.
* **Interactive UI:** Live Visualization of algorithm's expansion logic in real-time within a dedicated window. Algorithm's comparation is available too.
* **Testing:** All pathfinding strategies are tested.
* **Code Analysis:** Integrated support for code coverage tools.

## Technologies & Architecture
* **Language:** C++17.
* **Graphics:** SFML 3.0 (Simple and Fast Multimedia Library).
* **Build System:** CMake 3.16+ (Using FetchContent for external dependencies).
* **Testing:** Google Test (GTest) && Google Mock (GMock) && GCOV (Code Coverage).
* **Architecture:** **Strategy Design Pattern**. The algorithm logic is completely decoupled from the visualization engine, allowing for easy integration of new pathfinders. Architected is built using abstract interfaces to allow easily dependency injection and ensure high testability.

## Demo
https://github.com/user-attachments/assets/1a9d2205-90d1-4678-97ac-5103361fc446


## Installation & Setup
This project is fully optimized for VS Code. You can find the pre-configured tasks in .vscode/tasks.json. These tasks can be executed by pressing Ctrl+Shift+P -> Tasks: Run Task:
* **Build:** Compiles the main application.
* **Clean build:** Performs a fresh compilation from scratch (deletes and recreates the build/ folder).
* **Run App (SFML Visualization):** Launches the application using SFML visualizer.
* **Run App (Terminal Visualization):** Launches the application using Terminal visualizer.
* **Run Test:** Executes the Google Test suite and displays results in the terminal.
* **Generate code coverage:** Runs the tests and generates an HTML report.

## Extra
* **Cross-Platform Development & Testing:** Originally engineered in a macOS environment, the application has been tested on Linux (Ubuntu 20.04) to ensure seamless performance and reliable OpenGL context handling across different operating systems.

* **Standardized DevContainer Support:** The project includes a fully configured Development Container. This ensures a consistent environment, specifically standardizing the Coverage Reporting pipeline. By running reports inside a Linux-based container, we guarantee that coverage pipeline can be executed, independent of the host OS. Please note that the DevContainer is designed as a headless environment. It is highly recommended to use it for just running unit tests and test coverage. For the graphical visualization of algorithms, the application should be executed on the host OS to leverage native GPU acceleration and X11/Quartz windowing systems.

* **Modern Dependency Management (FetchContent):** Leveraging CMake's FetchContent module, the project automatically manages external dependencies (such as SFML, Json, Google Test and Google Mock) during the configuration step. This eliminates the need for manual library installations, ensuring a "clone and build" experience.
