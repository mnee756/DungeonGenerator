#include "Grid.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

Grid::Grid(int rows, int cols, float tileSize)
    : m_rows(rows), m_cols(cols), m_tileSize(tileSize) 
{
    
    initGrid();
    placeRooms();
}

int Grid::getRows() const {
    return m_rows;
}

int Grid::getCols() const {
    return m_cols;
}

float Grid::getTileSize() const {
    return m_tileSize;
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

bool Grid::makeRoom(int x, int y, int width, int height)
{
    // Check if the room fits in the grid without going out of bounds
    if (x + width >= m_cols || y + height >= m_rows) {
        return false;  // Room does not fit
    }
    // Check for overlap with existing rooms (i.e., non-empty tiles)
    for (int i = y; i < y + height; i++) {
        for (int j = x; j < x + width; j++) {
            if (grid[i][j].getType() != Empty) {
                return false;  // Overlap detected
            }
        }
    }
    // If all checks pass, place the room (fill grid with Floor tiles)
    for (int i = y; i < y + height; i++) {
        for (int j = x; j < x + width; j++) {
            grid[i][j].setType(Floor);  // Assuming 'Floor' is an enum type for empty space
        }
    }
    return true;  
}

void Grid::placeRooms(int numRooms, int maxAttempts) //probably want some input specifying relative size of rooms
{
    int area = m_rows * m_cols;
    int roomDims = sqrt(area / 10); //want a room to be roughly 1/10 size of grid
    int attempts = 0;

    for (int i = 0; i < numRooms; i++) {
        bool roomPlaced = false;

        while (attempts < maxAttempts && !roomPlaced) {
            int roomWidth = rand() % roomDims + 2;  // Random width between 3 and 8
            int roomHeight = rand() % roomDims + 2; // Random height between 3 and 8
            int x = rand() % (m_cols - roomWidth);
            int y = rand() % (m_rows - roomHeight);


            // Attempt to place the room with the given spacing
            if (makeRoom(x, y, roomWidth, roomHeight)) {
                roomPlaced = true;
            }
            else {
                attempts++;
            }
        } 
        if (attempts >= maxAttempts) {
            std::cout << "Max attempts reached for room placement. Stopping.\n";
            break;  // Stop if we exceed max attempts
        }
    }
}