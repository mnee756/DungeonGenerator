#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.h"

int main() {
    const int rows = 45;
    const int cols = 45;
    const float tileSize = 20.0f;

    sf::RenderWindow window(sf::VideoMode(cols * tileSize, rows * tileSize), "Dungeon Generator");
    Grid grid(rows, cols, tileSize);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        grid.draw(window);  // Draw the grid
        window.display();
    }

    return 0;
}
