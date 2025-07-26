#include "NodeType.h"
#include "Position.h"

class Node
{
private:
    long id_;
    Position position_;
    bool walkable_;
    bool visited_;
    NodeType type_;
    Node* parent_;
public:
    Node(long id, Position position, NodeType type, bool walkable);
    ~Node();

    bool isVisited();
    void setVisited(bool v);

    void setPosition(Position position);
    Position getPosition();

    Node& getParent();
    void setParent(Node& parent);

    void setType(NodeType type);
    NodeType getType();

    char getChar();
};
