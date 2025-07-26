#include <vector>
#include <string>

#include "Node.h"

class Grid
{
private:
    std::vector<std::vector<Node>> grid_;
    Node * startNode_;
    Node * endNode_;
public:
    Grid(std::vector<std::string> grid);
    ~Grid();

    void printGrid();
};
