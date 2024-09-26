#pragma once

#include <string>
#include <vector>

class Tile;

typedef std::vector<std::vector<Tile>> Map;
typedef std::vector<int> Position;

enum class Hostility {
    Hero,
    Enemy,
    Neutral,
    Allied
};

class Actor {
public:
    Actor(Hostility hostility, Position pos)
        : m_hostility(hostility), m_pos(pos) {}
    //virtual ~Actor();
    Hostility getHostility() const { return m_hostility; }  
    void setPos(Map& grid, Position dest);
    void add(Actor actor);

private:
    Hostility m_hostility{};
    int m_id{};
    Position m_pos{};
    int m_health{};
};

