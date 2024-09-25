#pragma once

#include <SFML/Graphics.hpp>

enum TileTexture 
{ 
    Empty,
    Floor,
    Wall,
    Water,
    ClosedDoor,
    OpenDoor,
};

class Tile {
public:
    Tile(TileTexture texture, int x, int y)
        : m_texture(texture), m_x(x), m_y(y) {};

    // Getters
    TileTexture getTexture() const { return m_texture; };
    int getX() const { return m_x; };
    int getY() const { return m_y; };

    // Setters
    void setTexture(TileTexture newTexture) { m_texture = newTexture; };
private:
    TileTexture m_texture;
    int m_x;
    int m_y;

    void updateColor();
};

