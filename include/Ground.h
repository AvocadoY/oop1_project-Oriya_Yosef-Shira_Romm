#pragma once
#include <SFML/Graphics.hpp>
#include "Standing.h"
#include "Const.h"

class Ground : public Standing
{
public:
	Ground(const sf::Vector2f& position, const sf::Texture& texture);
	void handleCollision(Object& object) override { object.handleCollision(*this); }
	void dig();                 
	//void handleCollision(Enemy& enemy) override;
	//void handleCollision(Player& player) override;
	void handleCollision(Digging& digging) override;
	bool isHole() const;
	void checkTime();

private:
	bool m_isHole;
	sf::Clock m_timer;
};