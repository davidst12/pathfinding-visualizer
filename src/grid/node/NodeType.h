#pragma once

// Enum para los tipos de nodo
enum class NodeType {
    EMPTY,  // Nodo vacío, donde se puede caminar
    WALL,   // Nodo muro, donde no se puede caminar
    START,  // Nodo de inicio
    END     // Nodo de fin
};