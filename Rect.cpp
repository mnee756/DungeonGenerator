#include "Rect.h"
#include <cmath>
#include "Math.h"
#include <iostream>

std::vector<int> Rect::center() const
{
    return { left + width() / 2 , bottom + height() / 2 };
}

bool Rect::makeRoom(std::vector<std::vector<Tile>>& grid)
{
    m_isConnected = true;
    room = Room(this->left, this->right, this->top, this->bottom);
    // If all checks pass, place the room (fill grid with Floor tiles)
    for (int i = room->left; i < room->right; i++) {
        for (int j = room->bottom; j < room->top; j++) {
            grid[j][i].setTexture(Floor);
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
    std::vector<std::vector<int>> points = pathfind(grid);      // return a point from each children on their edges
    connectCoords(points[0], points[1], grid);                  // connect the two points
    
}

std::vector<std::vector<int>> Rect::pathfind(std::vector<std::vector<Tile>>& grid)
{
    std::vector<int> p1 = (*children)[0].sampleFloor(grid);  // Starting point
    std::vector<int> p2 = (*children)[1].sampleFloor(grid);  // Ending point

    std::vector<int> start = p1;
    std::vector<int> end = p2;

    int x = start[0];
    int y = start[1];

    // Move horizontally from p1[0] to p2[0] on row p1[1]
    do {
        // Move toward p2[0]
        x += (p2[0] > x) ? 1 : -1;

        if (grid[p1[0]][x].getTexture() == Floor)
        {
            if ((*children)[0].pointIsIn(std::vector<int>{x, p1[0]}))
            {
                start = std::vector<int>{ x, p1[1] };
            }
            else if ((*children)[1].pointIsIn(std::vector<int>{x, p1[0]}))
            {
                end = std::vector<int>{ x, p1[0] };
                return { start, end };
            }
        }
    } while (x != p2[0]);

    // Move vertically from p1[1] to p2[1] (now x is aligned with p2[0])
    do {
        // Move toward p2[1]
        y += (p2[1] > y) ? 1 : -1;

        if (grid[y][p2[0]].getTexture() == Floor)
        {
            if ((*children)[0].pointIsIn(std::vector<int>{p2[0], y}))
            {
                start = std::vector<int>{ p2[1], y };
            }
            else if ((*children)[1].pointIsIn(std::vector<int>{p2[0], y}))
            {
                end = std::vector<int>{ p2[0], y };
                return { start, end };
            }
        }
    } while (y != p2[1]);

    std::cout << "This should not print\n";
    return { start, end }; // Return values in case no valid end is found
}

void Rect::connectCoords(std::vector<int> p1, std::vector<int> p2,
    std::vector<std::vector<Tile>>& grid)
{
    // Move horizontally from p1[0] to p2[0] on row p1[1]
    if (p1[0] <= p2[0]) {
        int start_x = std::min(p1[0], p2[0]);
        int end_x = std::max(p1[0], p2[0]);
        for (int x = start_x; x <= end_x; ++x) {
            if (p1[1] >= 0 && p1[1] < grid.size() && x >= 0 && x < grid[p1[1]].size()) {
                grid[p1[1]][x].setTexture(Floor);
            }
        }
    }

    // Move vertically from p1[1] to p2[1] on column p2[0]
    if (p1[1] <= p2[1]) {
        int start_y = std::min(p1[1], p2[1]);
        int end_y = std::max(p1[1], p2[1]);
        for (int y = start_y; y <= end_y; ++y) {
            if (y >= 0 && y < grid.size() && p2[0] >= 0 && p2[0] < grid[y].size()) {
                grid[y][p2[0]].setTexture(Floor);
            }
        }
    }
}
    

std::vector<int> Rect::sampleFloor(std::vector<std::vector<Tile>>& grid)
{
    bool isFloor{ false };
    int x{};
    int y{};
    while (!isFloor)
    {
        x = getRandom(left+1, right-1); //column
        y = getRandom(bottom+1, top-1); //row    
        if (grid[y][x].getTexture() == Floor)
        {
            isFloor = true;
        }
    }
    return std::vector<int>{x, y};
}

void Rect::addChild(Rect child) 
{
    if (!children) {
        children = std::vector<Rect>(); 
    }
    children->push_back(child); 
}

bool Rect::pointIsIn(std::vector<int> point) const
{
    if (point[0] >= left && point[0] <= right && point[1] >= bottom && point[1] <= top)
    {
        return true;
    }
    else
        return false;
}