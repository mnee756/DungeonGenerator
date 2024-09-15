#include "Rect.h"
#include <cmath>
#include <iostream>

std::vector<int> Rect::center() const
{
    return { left + width() / 2 , bottom + height() / 2 };
}

bool Rect::makeRoom(std::vector<std::vector<Tile>>& grid)
{
    m_isConnected = true; 
    room = Room( this->left, this->right, this->top, this->bottom );
    // If all checks pass, place the room (fill grid with Floor tiles)
    for (int i = room->left; i < room->right; i++) {
        for (int j = room->bottom; j < room->top; j++) {
            grid[j][i].setType(Floor);  
        }
    }
    return true;
}

bool Rect::connectRooms(std::vector<std::vector<Tile>>& grid)
{
    if (!children) 
    {
        // if no children, we are in a base room. Pass. 
        return false;
    }

    for (int i = 0; i < children->size(); i++)
    {
        if (!(*children)[i].m_isConnected) 
        {
            (*children)[i].connectRooms(grid);
        }
    }
    // once we get here all of the children should be connected within themselves.
    // connect them to each other.
    connectCoords((*children)[0].center(), (*children)[1].center(), grid);    
    m_isConnected = true;
    return true;
}

void Rect::connectCoords(std::vector<int> p1, std::vector<int> p2, 
    std::vector<std::vector<Tile>>& grid)
{
    // Move horizontally from p1[0] to p2[0] on row p1[1]
    if (p1[0] != p2[0]) {
        int start_x = std::min(p1[0], p2[0]);
        int end_x = std::max(p1[0], p2[0]);
        for (int x = start_x; x <= end_x; ++x) {
            if (p1[1] >= 0 && p1[1] < grid.size() && x >= 0 && x < grid[p1[1]].size()) {
                grid[p1[1]][x].setType(Floor);
            }
        }
    }

    // Move vertically from p1[1] to p2[1] on column p2[0]
    if (p1[1] != p2[1]) {
        int start_y = std::min(p1[1], p2[1]);
        int end_y = std::max(p1[1], p2[1]);
        for (int y = start_y; y <= end_y; ++y) {
            if (y >= 0 && y < grid.size() && p2[0] >= 0 && p2[0] < grid[y].size()) {
                grid[y][p2[0]].setType(Floor);
            }
        }
    }
}

void Rect::addChild(Rect child) 
{
    if (!children) {
        children = std::vector<Rect>(); 
    }
    children->push_back(child); 
}