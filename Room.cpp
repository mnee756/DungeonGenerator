#include "Room.h"
#include "Math.h"
#include <cmath>

Room::Room(Rect rect, RoomType type)
    : Rect(0,0,0,0), m_type(type)
{
    int wScale = static_cast<int>(std::ceil(rect.width() * 0.2));
    int hScale = static_cast<int>(std::ceil(rect.width() * 0.2));
    left = rect.left + getRandom(1, wScale);
    right = rect.right - getRandom(1, wScale);
    top = rect.top - getRandom(1, hScale);
    bottom = rect.bottom + getRandom(1, hScale);
};


