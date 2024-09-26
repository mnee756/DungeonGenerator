#include "Grid.h"
#include "Math.h"
#include "Actor.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

Grid::Grid(int rows, int cols, float tileSize, int maxRoomSize, int minRoomSize)
    : m_rows(rows), m_cols(cols), m_tileSize(tileSize), m_maxRoomSize(maxRoomSize), 
    m_minRoomSize(minRoomSize)
{

    initGrid();
    Rect BigRect = Rect(0, m_cols, 0, m_rows);          // no siblings or parents :(
    split(BigRect);                                     // BigRect now houses all rects and rooms. 
    BigRect.connectRooms(tiles); 
}

void Grid::setTile(int row, int col, TileTexture type) {
    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) 
    {
        tiles[row][col].setTexture(type);
    }
}

void Grid::initGrid() {
    tiles.clear();  // Clear the existing grid if needed

    for (int i = 0; i < m_rows; i++) {
        std::vector<Tile> row;
        for (int j = 0; j < m_cols; j++) {
            row.emplace_back(Empty, j, i);  // All tiles are Empty
        }
        tiles.push_back(row);
    }
}

void Grid::draw(sf::RenderWindow& window) const {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            sf::RectangleShape shape(sf::Vector2f(m_tileSize - 1, m_tileSize - 1));
            shape.setPosition(j * m_tileSize, i * m_tileSize);

            switch (tiles[i][j].getTexture())
            {
            case Empty:
                shape.setFillColor(sf::Color::White);
                break;
            case Wall:
                shape.setFillColor(sf::Color::Black);
                break;
            case Floor:
                shape.setFillColor(sf::Color::Magenta);
                break;
            default:
                shape.setFillColor(sf::Color::Green);  // Fallback color for unknown types
                break;
            }
            if (tiles[i][j].hasActor())
            {
                switch (tiles[i][j].getActor()->getHostility())
                {
                case Hostility::Hero:
                    shape.setFillColor(sf::Color::Yellow);
                    break;
                case Hostility::Enemy:
                    shape.setFillColor(sf::Color::Red);
                    break;
                case Hostility::Neutral:
                    shape.setFillColor(sf::Color::Green);
                    break;
                case Hostility::Allied:
                    shape.setFillColor(sf::Color::Blue);
                    break;
                default:
                    shape.setFillColor(sf::Color::Black);
                    break;
                }
                
            }

            window.draw(shape);
        }
    }
}

void Grid::split(Rect& rect)
{

    int w = rect.width();
    int h = rect.height();

    if (w > m_maxRoomSize && h < m_minRoomSize)
    {
        vSplit(rect);
    }
    else if (h > m_maxRoomSize && w < m_minRoomSize) 
    {
        hSplit(rect);
    }
    else if (((static_cast<float>(std::rand())/RAND_MAX) <= (static_cast<float>(m_minRoomSize * m_minRoomSize) / rect.area()) && w <= m_maxRoomSize && h <= m_maxRoomSize)
        || w < m_minRoomSize || h < m_minRoomSize)
    {
        // if not too big, or gets to a certain lower bound, make room. More probable the smaller the room is. 
        // make Room
        rect.makeRoom(tiles);
    }
    else
    {
        if ((static_cast<float>(std::rand()) / RAND_MAX) < static_cast<float>(w) / static_cast<float>(w + h))
        {
            vSplit(rect);
        }
        else
        {
            hSplit(rect);
        }
    }
}

void Grid::vSplit(Rect& rect)
{
    int div = getRandom(rect.left + 3, rect.right - 3);
    Rect child1 =  Rect(rect.left, div, rect.bottom, rect.top);
    Rect child2 = Rect(div, rect.right, rect.bottom, rect.top);
    split(child1);
    split(child2);
    rect.addChild(child1);
    rect.addChild(child2);   
}

void Grid::hSplit(Rect& rect)
{
    int div = getRandom(rect.bottom + 3, rect.top - 3);
    Rect child1 =  Rect(rect.left, rect.right, rect.bottom, div);
    Rect child2 = Rect(rect.left, rect.right, div, rect.top);
    split(child1);
    split(child2);
    rect.addChild(child1);
    rect.addChild(child2);
}