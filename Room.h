#pragma once
#include "Rect.h"

enum RoomType
{
    Normal,
    Treasure,
    Trap,
};

class Room : public Rect{
public:
    // Constructor
    Room(Rect rect, RoomType type = Normal);      

    // Getters
    RoomType getType() const { return m_type; };

    // Methods
    void setTiles();
private:
    RoomType m_type;
};
