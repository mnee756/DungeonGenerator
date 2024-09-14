#pragma once
#include "Room.h"
#include "Tile.h"
#include <optional>

class Rect {
public:
    int left, right, top, bottom;

    // Constructor
    Rect(int l = 0, int r = 0, int b = 0, int t = 0, 
        std::optional<std::vector<Rect>> children = std::nullopt, std::optional<Room> room = std::nullopt)
        : left(l), right(r), bottom(b), top(t), children(children), room(room) {}

    // Convenience methods
    int width() const { return right - left; }
    int height() const { return top - bottom; }
    int area() const { return width() * height(); }

    bool makeRoom(std::vector<std::vector<Tile>>& grid);
    bool connectRooms(std::vector<std::vector<Tile>>& grid);
    void addChild(Rect child);

private:
    std::optional<std::vector<Rect>> children;
    std::optional<Room> room;    
};