#pragma once
#include "Rect.h"

enum RoomType
{
    Normal,
    Treasure,
    Trap,
};

class Room {
public:
    // Constructor
    Room(Rect rect, RoomType type = Normal);      

    // Getters
    RoomType getType() const { return m_type; };

    // Methods
    void setTiles();
private:
    RoomType m_type;
    int m_right, m_left, m_bottom, m_top;
};
