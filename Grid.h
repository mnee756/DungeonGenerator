#pragma once

#include <vector>
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Grid {
public:
    Grid(int rows, int cols, float tileSize);

    // Getters
    int getRows() const;
    int getCols() const;
    float getTileSize() const;

    // Setters
    void setTile(int row, int col, TileType type);

    // Methods
    void draw(sf::RenderWindow& window) const;

private:
    int m_rows, m_cols;
    float m_tileSize;
    std::vector<std::vector<Tile>> grid;
    void initGrid();
    bool makeRoom(int x, int y, int width, int height);
    void placeRooms(int numRooms = 3, int maxAttempts = 3);
};

