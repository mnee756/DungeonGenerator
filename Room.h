#pragma once

enum RoomType
{
    Normal,
    Treasure,
    Trap,
};

class Room {
public:
    int left, right, top, bottom;
    // Constructor
    Room(int l, int r, int t, int b, RoomType type = Normal);      

    // Getters
    RoomType getType() const { return m_type; };

    // Methods
    void setTiles();
private:
    RoomType m_type;
};
