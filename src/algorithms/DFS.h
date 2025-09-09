#pragma once

#include <stack>
#include <vector>
#include <chrono>

#include "grid/Grid.h"
#include "common/AlgorithmResult.h"


/**
 * @class DFS
 * @brief Implementación del algoritmo Depth-First Search (DFS) sobre un grid de nodos.
 * 
 * El algoritmo DFS explora el grid de manera recursiva o utilizando una pila. En esta implementación
 * se usa una pila explícita (`std::stack`) para manejar los nodos a explorar.
 * 
 * Características:
 * - Expande los nodos en profundidad antes de retroceder.
 * - Puede no encontrar el camino más corto, pero es útil para exploración completa.
 * - Genera estadísticas de la ejecución, incluyendo número de nodos visitados y tiempo total.
 */
class DFS
{
public:
    /**
     * @brief Constructor de la clase DFS.
     * 
     * @param grid Referencia al grid sobre el cual se ejecutará el algoritmo.
     */
    DFS(Grid& grid);

    /**
     * @brief Ejecuta el algoritmo DFS.
     * 
     * Controla el ciclo principal del algoritmo: inicializa la pila con el nodo de inicio,
     * explora nodos en profundidad, y termina cuando se encuentra el nodo objetivo o 
     * se exploran todos los nodos posibles.
     */
    void runAlgorithm();
    
private:
    Grid& grid_; ///< Referencia al grid donde se realiza la búsqueda.
    
    std::stack<Node*> nodes_to_process_stack_; ///< Pila de nodos a procesar durante el algoritmo.
    
    AlgorithmResult result_; ///< Resultados del algoritmo (camino encontrado, estadísticas, etc.).
    
    /**
     * @brief Orden en que se comprobarán los vecinos de un nodo.
     * 
     * El orden es: Norte, Sur, Este, Oeste. Este orden afecta cómo se explora el grid,
     * y puede influir en el camino encontrado por DFS.
     */
    Position neighbors_check_order[4] = {
        Position(0, -1),  // North
        Position(0, 1),   // South
        Position(1, 0),   // East
        Position(-1, 0),  // West
    };

    /**
     * @brief Procesa el nodo actual en la pila.
     * 
     * Marca el nodo como visitado, asigna el nodo padre si corresponde, y llama
     * a la exploración de vecinos.
     */
    void processNode();

    /**
     * @brief Comprueba y agrega vecinos válidos del nodo actual.
     * 
     * Explora los nodos vecinos de `current_node`. Si un vecino:
     * - Está dentro de los límites del grid.
     * - Es transitable.
     * - No ha sido visitado aún.
     * 
     * Entonces se añade a la pila para ser procesado más adelante.
     * 
     * @param current_node Nodo actualmente en proceso.
     */
    void checkNeightbors(Node* current_node);

    /**
     * @brief Cambia el estado del algoritmo.
     * 
     * Actualiza el estado en `result_` para reflejar el progreso:
     * - IDLE
     * - RUNNING
     * - PATH_FOUND
     * - PATH_NOT_FOUND
     * 
     * @param state Nuevo estado del algoritmo.
     */
    void algorithmStateChange(AlgorithmState state);

    /**
     * @brief Reconstruye el camino encontrado.
     * 
     * Parte desde el nodo de fin y recorre los punteros `parent` hacia atrás
     * hasta llegar al nodo de inicio. El resultado es el camino en orden inverso,
     * que luego se invierte para devolverlo en el orden correcto.
     * 
     * @return Vector de nodos que representa el camino desde inicio hasta fin.
     */
    std::vector<Node> getPath();

    /**
     * @brief Genera estadísticas de ejecución del algoritmo.
     * 
     * Calcula:
     * - Tiempo total de ejecución (usando `std::chrono`).
     * - Número de nodos visitados.
     * - Ratio de nodos visitados respecto al total del grid.
     * 
     * Muestra los resultados en consola.
     */
    void generateStatistics();
};
