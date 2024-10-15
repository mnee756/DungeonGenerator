#include "Room.h"
#include "Mathf.h"
#include <cmath>

Room::Room(int l, int r, int t, int b, RoomType type)
    : left(l), right(r), top(t), bottom(b), m_type(type)
{
    int wScale = static_cast<int>(std::ceil((r-l) * 0.2));
    int hScale = static_cast<int>(std::ceil((t-b) * 0.2));
    left = l + getRandom(1, wScale);
    right = r - getRandom(1, wScale);
    top = t - getRandom(1, hScale);
    bottom = b + getRandom(1, hScale);
};

