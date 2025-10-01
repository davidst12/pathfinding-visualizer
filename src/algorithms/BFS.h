#pragma once

#include <queue>
#include <vector>
#include <chrono>

#include "algorithms/IAlgorithm.h"

/**
 * @class BFS
 * @brief Algoritmo de búsqueda en anchura (BFS) para encontrar el camino más corto entre dos nodos en una rejilla (Grid).
 * 
 * El algoritmo BFS (Breadth-First Search) se utiliza para encontrar el camino más corto entre un nodo de inicio y un nodo de fin en una rejilla.
 * Este algoritmo explora primero los nodos más cercanos al nodo de inicio, asegurando que el primer camino encontrado es el más corto posible.
 * 
 * BFS se implementa utilizando una estructura de datos tipo cola para almacenar los nodos por explorar. A medida que el algoritmo avanza, 
 * los nodos se expanden nivel por nivel (es decir, primero se exploran todos los nodos a una distancia de 1 del nodo de inicio, luego 
 * los nodos a una distancia de 2, etc.). 
 * 
 * El algoritmo se detiene cuando se encuentra el nodo de fin o cuando no hay más nodos por explorar.
 */
class BFS : public IAlgorithm
{
public:
    /**
     * @brief Constructor del algoritmo BFS.
     * 
     * Inicializa el algoritmo BFS con un Grid proporcionado y prepara las estructuras necesarias.
     * @param grid Referencia a la rejilla (Grid) donde se va a realizar la búsqueda.
     */
    BFS(Grid& grid);

    /**
     * @brief Ejecuta el algoritmo BFS.
     * 
     * Este método inicia la ejecución del algoritmo. Se encargará de procesar los nodos en la cola y 
     * buscar el camino más corto entre el nodo de inicio y el nodo de fin. 
     */
    void runAlgorithm() override;
    
private:
    //Grid grid_; ///< Rejilla donde se realiza la búsqueda.
    
    std::queue<Node*> nodes_to_process_queue_; ///< Cola de nodos a procesar durante el algoritmo.
    
    //AlgorithmResult result_; ///< Resultados del algoritmo (camino encontrado, estadísticas, etc.).
    
    /**
     * @brief Array que define el orden de comprobación de los vecinos de un nodo.
     * 
     * El orden es: Norte, Sur, Este, Oeste. Este orden determina cómo se explorarán los nodos vecinos
     * durante la ejecución del algoritmo BFS.
     */
    /*Position neighbors_check_order[4] = {
        Position(0, -1),  // North
        Position(0, 1),   // South
        Position(1, 0),   // East
        Position(-1, 0),  // West
    };*/

    /**
     * @brief Procesa el nodo actual en la cola.
     * 
     * Este método es responsable de procesar un nodo de la cola, marcarlo como visitado, 
     * y generar las nuevas posiciones a explorar.
     */
    void processNode() override;

    /**
     * @brief Comprueba los vecinos del nodo actual.
     * 
     * Este método explora los nodos vecinos del nodo actual y los añade a la cola de nodos 
     * a procesar si son válidos (es decir, si no han sido visitados y son caminables).
     * @param current_node Puntero al nodo actual que se está procesando.
     */
    void checkNeightbors(Node* current_node) override;

    /**
     * @brief Cambia el estado del algoritmo.
     * 
     * Actualiza el estado del algoritmo (por ejemplo, IDLE, RUNNING, PATH_FOUND, etc.).
     * @param state El nuevo estado del algoritmo.
     */
    void algorithmStateChange(AlgorithmState state) override;

    /**
     * @brief Obtiene el camino encontrado por el algoritmo.
     * 
     * Este método reconstruye el camino desde el nodo de fin hasta el nodo de inicio
     * utilizando los punteros de los nodos padres.
     * @return Un vector de nodos que representa el camino encontrado.
     */
    std::vector<Node> getPath() override;

    /**
     * @brief Genera y muestra por terminal las estadísticas del algoritmo.
     * 
     * Este método calcula y almacena las estadísticas del algoritmo (tiempo de ejecución, 
     * número de nodos visitados, etc.) para poder presentarlas al usuario.
     */
    void generateStatistics() override;
};
