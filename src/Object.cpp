#include "Object.h"

Object::Object(const sf::Vector2f& position, const sf::Texture& texture) :m_sprite(texture)
{
	m_sprite.setPosition(position);
}

void Object::draw(sf::RenderWindow& window) const //the same draw to all the objects
{
	window.draw(m_sprite);
}

sf::FloatRect Object::getGlobalBounds() const 
{
	return m_sprite.getGlobalBounds(); 
}
