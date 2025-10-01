#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <chrono>

#include "grid/node/Node.h"

/**
 * @enum AlgorithmState
 * @brief Enum que representa los posibles estados de un algoritmo de búsqueda de caminos.
 *
 * Este enum se utiliza para rastrear el estado de ejecución de los algoritmos de búsqueda de caminos.
 */
enum class AlgorithmState {
    IDLE,          ///< El algoritmo está inactivo y no se está ejecutando
    RUNNING,       ///< El algoritmo está en ejecución
    PATH_FOUND,    ///< El algoritmo ha encontrado un camino válido
    PATH_NOT_FOUND ///< El algoritmo no ha encontrado un camino válido
};

/**
 * @struct AlgorithmResult
 * @brief Estructura que almacena el resultado de la ejecución de un algoritmo de búsqueda de caminos.
 */
struct AlgorithmResult {
    AlgorithmState state = AlgorithmState::IDLE;  ///< Estado actual del algoritmo (idle, running, path found, etc.)
    std::vector<Node> path;                       ///< Camino encontrado por el algoritmo (si es que se encuentra un camino)
    int nodes_visited_count = 0;                  ///< Número de nodos visitados durante la ejecución del algoritmo
    float nodes_visited_ratio = 0;                ///< Proporción de nodos visitados respecto al total de nodos en la rejilla
    std::chrono::microseconds time;               ///< Tiempo de ejecución del algoritmo en microsegundos
};

/**
 * @brief Convierte un AlgorithmState a una cadena de texto para facilitar su visualización.
 * @return Una cadena representando el estado: IDLE, RUNNING, PATH_FOUND, PATH_NOT_FOUND.
 */
inline std::string state_to_string(AlgorithmState state)
{
   std::string enum_as_string;
   switch (state)
   {
        case AlgorithmState::IDLE:
            enum_as_string = "IDLE";
            break;
        case AlgorithmState::RUNNING:
            enum_as_string = "RUNNING";
            break;
        case AlgorithmState::PATH_FOUND:
            enum_as_string = "PATH_FOUND";
            break;
        case AlgorithmState::PATH_NOT_FOUND:
            enum_as_string = "PATH_NOT_FOUND";
            break;
        default:
            break;
   }
   return enum_as_string;
}
