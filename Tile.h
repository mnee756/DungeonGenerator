#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include <memory>


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
        : m_texture(texture), m_x(x), m_y(y), m_actor(nullptr) {};

    // Getters
    TileTexture getTexture() const { return m_texture; };
    int getX() const { return m_x; };
    int getY() const { return m_y; };
    bool hasActor() const { return m_actor != nullptr; }
    std::shared_ptr<Actor> getActor() const { return m_actor; }

    

    // Setters
    void setTexture(TileTexture newTexture) { m_texture = newTexture; };
    void setActor(std::shared_ptr<Actor> actor) { m_actor = actor; }
    void removeActor() { m_actor = nullptr; }
private:
    TileTexture m_texture;
    int m_x;
    int m_y;
    std::shared_ptr<Actor> m_actor;

    void updateColor();
};

