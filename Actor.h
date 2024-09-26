#pragma once

#include <string>
#include <vector>
#include <memory>

class Tile;
class Grid;

typedef std::vector<std::vector<Tile>> Map;
typedef std::vector<int> Position;

enum class Hostility {
    Hero,
    Enemy,
    Neutral,
    Allied
};

class Actor : public std::enable_shared_from_this<Actor> {
public:
    Actor(Hostility hostility, Position pos)
        : m_hostility(hostility), m_pos(pos) {}
    //virtual ~Actor();
    Hostility getHostility() const { return m_hostility; }  
    void setPos(Grid& grid, Position dest);
    void move(Grid& grid, Position mv);
    void addActorToTile(Grid& grid);

private:
    void removeActorFromTile(Grid& grid);
    Hostility m_hostility{};
    int m_id{};
    Position m_pos{};
    int m_health{};
};

