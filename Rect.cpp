#include "Rect.h"

bool Rect::makeRoom(std::vector<std::vector<Tile>>& grid)
{
    room = Room( this->left, this->right, this->top, this->bottom );
    // If all checks pass, place the room (fill grid with Floor tiles)
    for (int i = room->left; i < room->right; i++) {
        for (int j = room->bottom; j < room->top; j++) {
            grid[j][i].setType(Floor);  // Assuming 'Floor' is an enum type for empty space
        }
    }

    return true;
}

bool Rect::connectRooms(std::vector<std::vector<Tile>>& grid)
{
    Room room = Room(this->left, this->right, this->top, this->bottom);
    // If all checks pass, place the room (fill grid with Floor tiles)
    for (int i = room.left; i < room.right; i++) {
        for (int j = room.bottom; j < room.top; j++) {
            grid[j][i].setType(Floor);  // Assuming 'Floor' is an enum type for empty space
        }
    }

    return true;
}

void Rect::addChild(Rect child) 
{
    // Initialize children if it doesn't exist yet
    if (!children) {
        children = std::vector<Rect>(); // Initialize the vector inside the optional
    }
    children->push_back(child); // Add the child after ensuring the vector exists
}
