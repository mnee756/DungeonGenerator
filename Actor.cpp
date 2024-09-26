#include "Actor.h"
#include "Math.h"
#include "Grid.h"

void Actor::removeActorFromTile(Grid& grid) {
    grid.tiles[m_pos[1]][m_pos[0]].removeActor(); 
}

void Actor::addActorToTile(Grid& grid)
{
	grid.tiles[m_pos[1]][m_pos[0]].setActor(shared_from_this());
}

void Actor::setPos(Grid& grid, std::vector<int> dest)
{
	m_pos = dest;
}

void Actor::move(Grid& grid, Position mv)
{
	this->removeActorFromTile(grid);
	m_pos = m_pos + mv;
	this->addActorToTile(grid);
}
