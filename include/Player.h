#pragma once
#include <SFML/Graphics.hpp>
#include "Moving.h"
#include "Const.h"
#include "ResourceManager.h"
#include "Coin.h"
#include "Pole.h"

class Controller;

class Player : public Moving
{
public:
	Player(Controller &);
	void handleCollision(Object& other) override; 

	void handleCollision(Floor& Floor) override;
	void handleCollision(Ladder& ladder) override;
	void handleCollision(Pole& pole) override;
	void handleCollision(Ground& ground) override;
	void handleCollision(Coin& coin) override;
	void handleCollision(Enemy& enemy) override;
	
	int getLifes() const;
	int getScore() const;
	void init();
	void newLevel();
	void handleInput();
	void checkOutOfBound(float boardWidth, float boardHeight) override;
	void timesUp();
private:
	int m_lifes;
	int m_score;
	Controller& m_controller;
	sf::Sound m_enemySound;
	sf::Sound m_coinSound;
	sf::Sound m_shovelSound;
	void handleDirection() override;
};