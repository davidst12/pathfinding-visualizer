#pragma once

#include <string>

/**
 * @struct Position
 * @brief Estructura que representa una posición 2D en la rejilla.
 *
 * La estructura `Position` es utilizada para almacenar las coordenadas `x` y `y` de un nodo en la rejilla.
 * Esta estructura es clave para representar posiciones dentro de la rejilla y realizar operaciones de comparación
 * o movimientos entre posiciones (como en los algoritmos de búsqueda).
 */
struct Position {
    int x;  ///< Coordenada X de la posición en la rejilla (columna)
    int y;  ///< Coordenada Y de la posición en la rejilla (fila)

    /**
     * @brief Constructor para crear una posición con coordenadas específicas.
     * @param x Coordenada X de la posición.
     * @param y Coordenada Y de la posición.
     */
    Position(int x = 0, int y = 0) : x(x), y(y) {}

    /**
     * @brief Operador de comparación para verificar si dos posiciones son iguales.
     * @param other Otra posición para comparar.
     * @return Verdadero si las posiciones son iguales, falso en caso contrario.
     */
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    /**
     * @brief Operador de suma para realizar movimientos entre posiciones (por ejemplo, para explorar vecinos).
     * @param other Posición a sumar a la actual.
     * @return Una nueva posición resultante de la suma de las dos posiciones.
     */
    Position operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
    }

    /**
     * @brief Convierte la posición a una cadena de texto para facilitar su visualización.
     * @return Una cadena representando la posición en formato "{x, y}".
     */
    std::string to_string() {
        return "{" + std::to_string(x) + " , " + std::to_string(y) + "}";
    }
};
