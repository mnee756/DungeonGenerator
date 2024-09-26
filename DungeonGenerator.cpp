#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Grid.h"
#include "Actor.h"

void handleInput(std::shared_ptr<Actor> hero, Grid& grid, sf::Event& event) {
    std::vector<int> moveCommand = { 0, 0 };

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::W:
            moveCommand[1] -= 1;  // Move up
            break;
        case sf::Keyboard::S:
            moveCommand[1] += 1;  // Move down
            break;
        case sf::Keyboard::A:
            moveCommand[0] -= 1;  // Move left
            break;
        case sf::Keyboard::D:
            moveCommand[0] += 1;  // Move right
            break;
        default:
            break;
        }

        // Move the hero if there's a movement command
        if (moveCommand != std::vector<int>({ 0, 0 })) {
            hero->move(grid, moveCommand);  // Move the hero
        }
    }
}


int main() {
    const int rows = 45;
    const int cols = 45;
    const float tileSize = 20.0f;

    sf::RenderWindow window(sf::VideoMode(cols * tileSize, rows * tileSize), "Dungeon Generator");
    Grid grid(rows, cols, tileSize);
    std::shared_ptr<Actor> hero = std::make_shared<Actor>(Hostility::Hero, std::vector<int>({ 5, 5 }));
    grid.tiles[5][5].setActor(hero);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } 
            handleInput(hero, grid, event);  // Handle user inputs and move the hero
        }

       

        window.clear();
        grid.draw(window);  // Draw the grid
        window.display();
    }

    return 0;
}
