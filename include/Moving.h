#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include <iostream>
class Controller;

class Moving : public Object
{
public:
	Moving(const sf::Vector2f& position, const sf::Texture& texture, float speed);
	void move(sf::Time);
	//void setDirection(const sf::Vector2f& dir);
	virtual void handleDirection() = 0;
	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition() const;
	void setStartingPos(const sf::Vector2f& position);	
	void stopVelocityX(); 
	void stopVelocityY(); 

	//sf::Vector2f getPrevPos() const { return m_prevPos; }
	virtual void checkOutOfBound(float,float) = 0;
	
protected:
	sf::Vector2f m_direction;
	sf::Vector2f m_startingPos;
	//sf::Vector2f m_prevPos;
	sf::Vector2f m_velocity;
	void resolveBlockingCollision(const sf::FloatRect& );
	void falling(const sf::FloatRect& holeBounds);
	void handleBoardEdges(const sf::Vector2f& pos, float boardWidth);
	bool holeBetweenFloor(Controller&);
	bool m_applyGravity;
	bool m_onLadder;
	bool m_onPole;
private:
	float m_speedPerSecond;
};