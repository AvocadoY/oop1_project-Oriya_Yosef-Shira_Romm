#pragma once
#include <SFML/Graphics.hpp>
#include "Const.h"
#include "ResourceManager.h"
//class Land;

class Player;
class Enemy;
class Floor;
class Ground;
class Ladder;
class Coin;
class Pole;
class Digging;

class Object
{
public:
	Object(const sf::Vector2f& position, const sf::Texture& texture);
	virtual void draw(sf::RenderWindow&) const;
	virtual ~Object() = default;
	// { return m_isDisposed; }

	// מסמן את האובייקט למחיקה (הפונקציה החדשה)
	 //{ m_isDisposed = true; }
	//float getPosition() const;
	//checkPlace()=0
	sf::FloatRect getGlobalBounds() const;// { return m_sprite.getGlobalBounds(); }

	virtual void handleCollision(Object& other) = 0;
	//virtual void handleCollision(Land& land) = 0;
	// 
	//void setPhoto(const sf::Texture& texture);
	virtual void handleCollision(Player&) {}
	virtual void handleCollision(Enemy&) {}
	virtual void handleCollision(Floor&) {}
	virtual void handleCollision(Ground&) {}
	virtual void handleCollision(Ladder&) {}
	virtual void handleCollision(Coin&) {}
	virtual void handleCollision(Pole&) {}
	virtual void handleCollision(Digging&) {}


	bool checkCollision(const Object& object) const
	{
		return m_sprite.getGlobalBounds().findIntersection(object.m_sprite.getGlobalBounds()).has_value();
	}
	
protected:
	//private:
	sf::Sprite m_sprite;
};