#pragma once

/**
 * @struct GridInfo
 * @brief Estructura que almacena la información básica sobre el tamaño y los nodos de la rejilla.
 *
 * Se utiliza para facilitar el cálculo de estadísticas relacionadas con el grid y sus nodos
 * en el contexto de los algoritmos de búsqueda de caminos.
 */
struct GridInfo {
    int width_;              ///< Ancho de la rejilla (número de columnas)
    int height_;             ///< Alto de la rejilla (número de filas)
    int empty_nodes_count_;  ///< Número de nodos vacíos (donde se puede caminar)
    int total_nodes_count_;  ///< Número total de nodos (vacíos + muros)
};