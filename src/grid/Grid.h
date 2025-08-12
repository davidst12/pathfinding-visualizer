#pragma once

#include <vector>
#include <string>

#include "node/Node.h"
#include "GridInfo.h"

/**
 * @class Grid
 * @brief Representa un grid 2D de nodos para ser utilizado por los algoritmos de búsqueda.
 * 
 * Esta clase maneja la creación de un grid con diferentes tipos de nodos (vacíos, muros, inicio, fin),
 * y provee métodos para manipular y acceder a los nodos dentro de este grid.
 * 
 * Los nodos son representados por la clase Node, la cual guarda información sobre la posición y el tipo.
 */
class Grid
{
private:

    std::vector<std::vector<Node>> grid_; ///< Matriz 2D que almacena los nodos del grid

public:
    /**
     * @brief Constructor de la clase Grid.
     * 
     * Inicializa la rejilla 2D a partir de una representación de texto (una lista de strings). Cada string representa
     * una fila de la rejilla, y los caracteres dentro del string indican el tipo de nodo (vacío, muro, inicio, fin).
     * 
     * @param grid Un vector de strings que representa el grid.
     */
    Grid(std::vector<std::string> grid);

    Node* startNode_; ///< Nodo de inicio del algoritmo
    Node* endNode_;   ///< Nodo de fin del algoritmo
    GridInfo grid_info_; ///< Información adicional del Grid

    /**
     * @brief Imprime la representación del grid en la consola.
     * 
     * Este método recorre la matriz 2D de nodos y imprime una representación visual del grid en la consola.
     * Cada nodo se representa por un carácter según su tipo (por ejemplo, 'X' para muros, 'O' para nodos vacíos).
     */
    void printGrid();

    /**
     * @brief Imprime la representación del grid junto con el camino encontrado.
     * 
     * Este método imprime el grid visualmente y luego sobrepone el camino encontrado por el algoritmo de búsqueda.
     * El camino se pasa como un vector de nodos, y se representa de una manera diferente en la visualización.
     * 
     * @param path El camino encontrado, representado como un vector de nodos.
     */
    void printGridAndPath(std::vector<Node> path);

    /**
     * @brief Obtiene un nodo de la rejilla a partir de su posición.
     * 
     * Este método permite acceder a un nodo en la rejilla dado su par de coordenadas (x, y).
     * 
     * @param pos La posición del nodo en el grid.
     * @return Un puntero al nodo correspondiente en esa posición.
     */
    Node* getNodeFromPosition(Position pos);

    /**
     * @brief Obtiene la altura del grid.
     * La altura es el número de filas en el grid (el número de nodos en la dirección vertical).
     */
    int getGridHeight();

    /**
     * @brief Obtiene el ancho del grid.
     * El ancho es el número de columnas en el grid (el número de nodos en la dirección horizontal).
     */
    int getGridWidth();

    /**
     * @brief Obtiene el número de nodos vacíos en el grid.
     * Los nodos vacíos son aquellos que están marcados como transitable (no son muros ni nodos de inicio o fin).
     */
    int getEmptyNodesCount();

    /**
     * @brief Obtiene el número total de nodos en el grid.
     * El número total de nodos es simplemente el número de filas multiplicado por el número de columnas en el grid.
     */
    int getTotalNodesCount();

    /**
     * @brief Verifica la validez de una posición en el grid.
     * 
     * Este método asegura que las coordenadas (x, y) estén dentro de los límites del grid y que no se trate
     * de una posición inválida (por ejemplo, fuera del rango de filas o columnas).
     * 
     * @param pos La posición a verificar.
     * @return true si la posición es válida dentro del grid, false en caso contrario.
     */
    bool checkPositionValidity(Position pos);

};