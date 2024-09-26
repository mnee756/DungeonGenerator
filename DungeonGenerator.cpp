#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Grid.h"
#include "Actor.h"

int main() {
    const int rows = 45;
    const int cols = 45;
    const float tileSize = 20.0f;

    sf::RenderWindow window(sf::VideoMode(cols * tileSize, rows * tileSize), "Dungeon Generator");
    Grid grid(rows, cols, tileSize);
    //Actor hero(Hostility::Hero, std::vector<int>( {5, 5}) );
    std::shared_ptr<Actor> hero = std::make_shared<Actor>(Hostility::Hero, std::vector<int>({ 5, 5 }));
    grid.grid[5][5].setActor(hero);


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
