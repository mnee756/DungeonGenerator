#pragma once

enum RoomType
{
    Normal,
    Treasure,
    Trap,
};

class Room {
public:
    // Constructor
    Room(RoomType type, int x, int y, int width, int height)
        : m_type(type), m_x(x), m_y(y), m_width(width), m_height(height) {};

    // Getters
    int getX() const { return m_x; };
    int getY() const { return m_y; };
    int getWidth() const { return m_width; };
    int getHeight() const { return m_height; };
    RoomType getType() const { return m_type; };

    // Methods
    bool intersects(const Room& other) const;

private:
    RoomType m_type;
    int m_x, m_y;
    int m_width, m_height;
};
