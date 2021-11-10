#include "AStar.h"

#include <list>
#include <algorithm>

using std::list;
void PathFinding::initPathfinding(int width,int height,vector<Cube>& cubes)
{
    //Create the nodes.
    m_nodes = vector<s_Node*>(width * height);
    for (size_t i = 0; i < width * height; i++)
    {
        m_nodes[i] = new s_Node();
    }
    
    //Populate each node based on the grid position cube type.
    m_grid_Width = width;
    m_grid_Height = height;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            Vector2 cubePos = cubes[(i * width) + j].getTilePos();
            m_nodes[(i * width) + j]->m_pos_X = cubePos.x;
            m_nodes[(i * width) + j]->m_pos_Y = cubePos.y;
            m_nodes[(i * width) + j]->m_wall = ((cubes[(i * width) + j].GetCubeType() == CubeType::WALL) ? true : false); 
            m_nodes[(i * width) + j]->m_parent = nullptr;
            m_nodes[(i * width) + j]->m_is_Visited = false;
        }
    }

    //Populate each node neighbouring nodes.
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if(i > 0)
            {
                m_nodes[(i * width) + j]->m_neighbours.push_back(m_nodes[((i - 1) * width) + j]);
            }
            if(i < (height - 1))
            {
                m_nodes[(i * width) + j]->m_neighbours.push_back(m_nodes[((i + 1) * width) + j]);
            }
            if(j > 0)
            {
                m_nodes[(i * width) + j]->m_neighbours.push_back(m_nodes[(i * width) + (j - 1)]);
            }
            if(j < (width - 1))
            {
                m_nodes[(i * width) + j]->m_neighbours.push_back(m_nodes[(i * width) + (j + 1)]);
            }
        }
        
    }
}

//Get a path from the starting point to the ending point.
vector<Vector2> PathFinding::getPath(Vector2& startingPoint, Vector2& endPoint)
{
    //Reset all nodes.
    for (size_t i = 0; i < m_grid_Height; i++)
    {
        for (size_t j = 0; j < m_grid_Width; j++)
        {
            m_nodes[(i * m_grid_Width) + j]->m_is_Visited = false;
            m_nodes[(i * m_grid_Width) + j]->m_global_Value = INFINITY;
            m_nodes[(i * m_grid_Width) + j]->m_local_Value = INFINITY;
            m_nodes[(i * m_grid_Width) + j]->m_parent = nullptr;
        }
    }

    //Get the starting and ending node.
    s_Node* endNode = getNode(endPoint);
    s_Node* startNode = getNode(startingPoint);
    s_Node* currentNode = startNode;
    currentNode->m_local_Value = 0.0f;
    currentNode->m_global_Value = Vector2::distance(startingPoint,endPoint);

    list<s_Node*> listNotTestedNodes;
    listNotTestedNodes.push_back(startNode);

    //Go over each node in the not tested list.
    while (!listNotTestedNodes.empty() && currentNode != endNode)
    {
        //Sort the list by the smaller global value.
        listNotTestedNodes.sort([](const s_Node* lhs, const s_Node* rhs) {return lhs->m_global_Value < rhs->m_global_Value;});

        //As long as the list is not empty and you get a node you did not visit, keep going through it.
        while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->m_is_Visited)
        {
            listNotTestedNodes.pop_front();
        }
        
        //If the list is empty, break.
        if(listNotTestedNodes.empty())
        {
            break;
        } 

        currentNode = listNotTestedNodes.front();
        currentNode->m_is_Visited = true;

        //Check each of the node neighbours.
        for(auto nodeNeighbour : currentNode->m_neighbours)
        {
            //If the node is not a wall and not visited add him to the list.
            if(!nodeNeighbour->m_is_Visited && nodeNeighbour->m_wall == 0)
            {
                listNotTestedNodes.push_back(nodeNeighbour);
            }

            float possibleLowerValue = currentNode->m_local_Value + getNodesDistance(currentNode,nodeNeighbour);

            //Get the lower local value neighbour.
            if(possibleLowerValue < nodeNeighbour->m_local_Value)
            {
                nodeNeighbour->m_parent = currentNode;
                nodeNeighbour->m_local_Value = possibleLowerValue;

                nodeNeighbour->m_global_Value = nodeNeighbour->m_local_Value + getNodesDistance(nodeNeighbour,endNode);
            }
        }  
    }
    
    s_Node* p = endNode;
    vector<Vector2> path = vector<Vector2>();
    
    //Go back for each parent to create a path from end to start.
    while (p->m_parent != nullptr)
    {
        path.push_back(nodeToVector2(p));
        p = p->m_parent;
    }

    //Return the reversed path.
    std::reverse(path.begin(),path.end());
    return path;
}
Vector2 PathFinding::nodeToVector2(s_Node* node) const
{
    Vector2 pos =Vector2(node->m_pos_X,node->m_pos_Y); 
    return pos;
}
float PathFinding::getNodesDistance(s_Node* a,s_Node* b) const
{
    return sqrtf((a->m_pos_X - b->m_pos_X) * (a->m_pos_X - b->m_pos_X) + (a->m_pos_Y - b->m_pos_Y) * (a->m_pos_Y - b->m_pos_Y));
}
s_Node* PathFinding::getNode(Vector2& position) const
{
    int j = position.x;
    int i = position.y;
    return m_nodes[(i * m_grid_Width) + j];
}