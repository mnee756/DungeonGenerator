#pragma once

#include <vector>
#include "Tile.h"
#include "Rect.h"
#include "Room.h"
#include <SFML/Graphics.hpp>

class Grid : public Rect {
public:
    Grid(int rows, int cols, float tileSize, int maxRoomSize = 20, int minRoomSize = 14);
    std::vector<std::vector<Tile>> grid;
    // Getters
    int getRows() const { return m_rows; };
    int getCols() const { return m_cols; };
    float getTileSize() const { return m_tileSize; };

    // Setters
    void setTile(int row, int col, TileTexture type);

    // Methods
    void draw(sf::RenderWindow& window) const;

private:
    int m_rows, m_cols;
    int m_maxRoomSize;
    int m_minRoomSize;
    float m_tileSize;
    
    std::vector<Room> m_rooms;

    void initGrid();
    void hSplit(Rect& rect);
    void vSplit(Rect& rect);
    void split(Rect& rect);
};

