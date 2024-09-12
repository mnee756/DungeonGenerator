#include "Room.h"

bool Room::intersects(const Room& other) const {
    return !(m_x + m_width <= other.m_x ||  // Room is to the left
        m_x >= other.m_x + other.m_width ||  // Room is to the right
        m_y + m_height <= other.m_y ||  // Room is above
        m_y >= other.m_y + other.m_height);  // Room is below
}