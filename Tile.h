#pragma once

#include <SFML/Graphics.hpp>

enum TileType 
{ 
    Empty,
    Floor,
    Wall,
    Player,
    Enemy,
    Door,
};

class Tile {
public:
    Tile(TileType type, int x, int y)
        : m_type(type), m_x(x), m_y(y) {};

    // Getters
    TileType getType() const { return m_type; };
    int getX() const { return m_x; };
    int getY() const { return m_y; };

    // Setters
    void setType(TileType newType) { m_type = newType; };
private:
    TileType m_type;
    int m_x;
    int m_y;

    void updateColor();
};

