#include "Room.h"

Room::Room(Rect rect, RoomType type)
    : m_type(type), m_left(rect.left), m_right(rect.right),
    m_bottom(rect.bottom), m_top(rect.top) 
{
};


