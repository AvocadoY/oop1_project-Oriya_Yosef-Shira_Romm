#include "Coin.h"

Coin::Coin(const sf::Vector2f& position, const sf::Texture& texture) : Standing(position,texture)
{
	m_taken = false;
}

void Coin::handleCollision(Object& object)
{
    object.handleCollision(*this);
}


void Coin::handleCollision(Player& player)
{
    m_taken = true; 
}

bool Coin::isTaken() const
{
    return m_taken;
}