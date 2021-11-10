#ifndef ASTAR_H
#define ASTAR_H

#include "Cube.h"
#include <vector>

using std::vector;

struct s_Node
{
    bool m_wall = false;
    bool m_is_Visited = false;
    float m_global_Value;
    float m_local_Value;
    int m_pos_X;
    int m_pos_Y;
    vector<s_Node*> m_neighbours;
    s_Node* m_parent;
};

class PathFinding
{
    public:
        PathFinding() = default;
        ~PathFinding() = default;
        void initPathfinding(int width,int height, vector<Cube>& cubes);
        vector<Vector2> getPath(Vector2& startingPoint, Vector2& endPoint);
    private:

    float getNodesDistance(s_Node* a,s_Node* b) const;
    Vector2 nodeToVector2(s_Node* node) const;
    s_Node* getNode(Vector2& position) const;
    vector<s_Node*> m_nodes;
    int m_grid_Width {22};
    int m_grid_Height {28};
};

#endif