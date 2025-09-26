#pragma once

// Enum para los tipos de nodo
enum class NodeType {
    EMPTY,  // Nodo vacío, donde se puede caminar
    WALL,   // Nodo muro, donde no se puede caminar
    START,  // Nodo de inicio
    END,    // Nodo de fin
    ROAD,   // Nodo camino
    GRASS,  // Nodo césped, terreno con mayor coste de movimiento
    WATER   // Nodo agua, terreno con mucho mayor coste de movimiento
};