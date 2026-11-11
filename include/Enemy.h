#pragma once
#include <SFML/Graphics.hpp>
#include "Moving.h"
#include "Const.h"
class Controller;

class Enemy : public Moving
{
public:
	Enemy(const sf::Vector2f& position, const sf::Texture& texture,Controller &cotroller);
	void handleCollision(Object& object) override;

	
	void handleCollision(Floor& floor) override;
	void handleCollision(Player& player) override;
	void handleCollision(Ground& ground) override;
	void handleCollision(Ladder& ladder) override;
	void handleCollision(Pole& pole) override;
	void checkOutOfBound(float boardWidth, float boardHeight) override;
	
private:
	void handleDirection() override;
	Controller& m_controller;
	bool m_trapped;
	int getBestColumn(int myRow, int myCol, int playerRow);
};