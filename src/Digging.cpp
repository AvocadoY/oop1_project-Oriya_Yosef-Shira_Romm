#include "Digging.h"
#include "ResourceManager.h"
#include "Board.h"

Digging::Digging(const sf::Vector2f position, Board* board)
	: Object(position, ResourceManager::getInstance().getTexture(ResourceManager::Empty)),
	m_board(board)
{ }

void Digging::handleCollision(Object& other) 
{ 
	other.handleCollision(*this); 
}

void Digging::handleCollision(Ground& ground) 
{ 
	m_board->addHole(ground);
}
