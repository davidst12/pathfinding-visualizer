#pragma once

#include "NodeType.h"
#include "Position.h"

/**
 * @class Node
 * @brief Representa un nodo en una rejilla (Grid) en el contexto de un algoritmo de búsqueda de camino.
 * 
 * La clase Node es una representación de un nodo en una estructura de datos como una rejilla (grid) o grafo.
 * Cada nodo tiene una posición, un tipo (vacío, muro, inicio, fin), un estado de visitado, un puntero al nodo padre.
 */
class Node
{
public:
    /**
     * @brief Constructor del nodo.
     * 
     * Crea un nodo con una posición específica, un tipo (vacío, muro, inicio, fin) y una propiedad de "caminabilidad".
     * @param position La posición del nodo dentro de la rejilla.
     * @param type El tipo del nodo (vacío, muro, inicio, fin).
     */
    Node(Position position, NodeType type);

    /**
     * @brief Verifica si el nodo ha sido visitado.
     * @return true si el nodo ha sido visitado, false si no lo ha sido.
     */
    bool isVisited();

    /**
     * @brief Establece si el nodo ha sido visitado.
     * @param v El valor booleano que indica si el nodo ha sido visitado o no.
     */
    void setVisited(bool v);

    /**
     * @brief Establece la posición del nodo.
     * @param position La nueva posición que se desea asignar al nodo.
     */
    void setPosition(Position position);

    /**
     * @brief Obtiene la posición del nodo.
     * @return La posición del nodo como un objeto de tipo Position.
     */
    Position getPosition();

    /**
     * @brief Obtiene el nodo padre.
     * 
     * Este método devuelve un puntero al nodo padre, que es útil para reconstruir el camino una vez que se ha encontrado 
     * una ruta de solución en los algoritmos de búsqueda.
     * @return El puntero al nodo padre.
     */
    Node* getParent();

    /**
     * @brief Establece el nodo padre.
     * @param parent El puntero al nodo padre que se quiere asignar.
     */
    void setParent(Node* parent);

    /**
     * @brief Establece el tipo del nodo.
     * @param type El tipo del nodo (vacío, muro, inicio, fin).
     */
    void setType(NodeType type);

    /**
     * @brief Obtiene el tipo del nodo.
     * @return El tipo del nodo (vacío, muro, inicio, fin).
     */
    NodeType getType();

    /**
     * @brief Obtiene el carácter asociado al tipo del nodo.
     * 
     * Este método devuelve un carácter que representa el nodo en la rejilla visual. 
     * Por ejemplo, un nodo vacío podría representarse como 'O', un muro como 'X', etc.
     * @return El carácter que representa el tipo del nodo.
     */
    char getChar();

    /**
     * @brief Imprime la información completa del nodo.
     * 
     * Este método imprime detalles relevantes del nodo, como su posición, tipo y si ha sido visitado.
     */
    void printNodeInformation();

private:
    Position position_; ///< La posición del nodo en la rejilla.
    bool visited_;      ///< Indica si el nodo ha sido visitado durante la ejecución de un algoritmo.
    NodeType type_;     ///< El tipo de nodo (vacío, muro, inicio, fin).
    Node* parent_;      ///< Puntero al nodo padre (utilizado en algoritmos de búsqueda).
};

