#include "Grid.h"
#include "Math.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

Grid::Grid(int rows, int cols, float tileSize, int maxRoomSize, int minRoomSize)
    : m_rows(rows), m_cols(cols), m_tileSize(tileSize), m_maxRoomSize(maxRoomSize), 
    m_minRoomSize(minRoomSize)
{

    initGrid();
    //makeRoom(Rect(4, 6, 14, 16));
    split(Rect(0, m_cols, 0, m_rows));
    /*
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    std::cout << getRandom(-3, 33) << '\n';
    */
}

void Grid::setTile(int row, int col, TileType type) {
    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) 
    {
        grid[row][col].setType(type);
    }
}

void Grid::initGrid() {
    grid.clear();  // Clear the existing grid if needed

    for (int i = 0; i < m_rows; i++) {
        std::vector<Tile> row;
        for (int j = 0; j < m_cols; j++) {
            row.emplace_back(Empty, j, i);  // All tiles are Empty
        }
        grid.push_back(row);
    }
}

void Grid::draw(sf::RenderWindow& window) const {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            sf::RectangleShape shape(sf::Vector2f(m_tileSize - 1, m_tileSize - 1));
            shape.setPosition(j * m_tileSize, i * m_tileSize);

            switch (grid[i][j].getType())
            {
            case Empty:
                shape.setFillColor(sf::Color::White);
                break;
            case Wall:
                shape.setFillColor(sf::Color::Black);
                break;
            case Player:
                shape.setFillColor(sf::Color::Blue);  
                break;
            case Enemy:
                shape.setFillColor(sf::Color::Red); 
                break;
            case Floor:
                shape.setFillColor(sf::Color::Magenta);
                break;
            default:
                shape.setFillColor(sf::Color::Green);  // Fallback color for unknown types
                break;
            }

            window.draw(shape);
        }
    }
}

bool Grid::makeRoom(Rect rect)
{
    // Check if the room fits in the grid without going out of bounds
    if (rect.right > m_cols || rect.left < 0 || rect.top > m_rows || rect.bottom < 0) {
        return false;  // Room does not fit
    }
    // Check for overlap with existing rooms (i.e., non-empty tiles)
    
    // If all checks pass, place the room (fill grid with Floor tiles)
    for (int i = rect.left; i < rect.right; i++) {
        for (int j = rect.bottom; j < rect.top; j++) {
            grid[j][i].setType(Floor);  // Assuming 'Floor' is an enum type for empty space
        }
    }
    return true;  
}

void Grid::connectRooms()
{

}

void Grid::split(Rect rect)
{

    int w = rect.width();
    int h = rect.height();

    if (w > m_maxRoomSize && h < m_minRoomSize)
    {
        vSplit(rect);
    }
    else if (h > m_maxRoomSize && h < m_minRoomSize) 
    {
        hSplit(rect);
    }
    else if (((static_cast<float>(std::rand())/RAND_MAX) <= (m_minRoomSize * m_minRoomSize / rect.area()) && w <= m_maxRoomSize && h <= m_maxRoomSize)
        || w < m_minRoomSize || h < m_minRoomSize)
    {
        // if not too big, or gets to a certain lower bound, make room. More probable the smaller the room is. 
        // make Room
        makeRoom(rect);
    }
    else
    {
        if ((static_cast<float>(std::rand()) / RAND_MAX) < (w - 2) / (w + h - 4))
        {
            vSplit(rect);
        }
        else
        {
            hSplit(rect);
        }
    }
}

void Grid::vSplit(Rect rect)
{
    int div = getRandom(rect.left + 3, rect.right - 3);
    split(Rect(rect.left, div, rect.bottom, rect.top));
    split(Rect(div, rect.right, rect.bottom, rect.top));
}

void Grid::hSplit(Rect rect)
{
    int div = getRandom(rect.bottom + 3, rect.top - 3);
    split(Rect(rect.left, rect.right, rect.bottom, div));
    split(Rect(rect.left, rect.right, div, rect.top));
}