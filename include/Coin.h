#pragma once
#include <SFML/Graphics.hpp>
#include "Standing.h"
#include "ResourceManager.h"

class Coin : public Standing
{
public:
	Coin(const sf::Vector2f& position, const sf::Texture& texture);
	bool isTaken() const;
    void handleCollision(Object& object) override;

    void handleCollision(Player& player) override;
   
private:
	bool m_taken;
};