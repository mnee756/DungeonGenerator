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
    Tile(TileType type, int x, int y);

    // Getters
    TileType getType() const;
    int getX() const;
    int getY() const;

    // Setters
    void setType(TileType newType);
private:
    TileType type;
    int m_x;
    int m_y;

    void updateColor();
};

