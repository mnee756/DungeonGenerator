#include "Tile.h"

Tile::Tile(TileType type, int x, int y)
    : type(type), m_x(x), m_y(y) {}

TileType Tile::getType() const {
    return type;
}

int Tile::getX() const {
    return m_x;
}

int Tile::getY() const {
    return m_y;
}

void Tile::setType(TileType newType) {
    type = newType;
}
