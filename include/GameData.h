#pragma once
#include <SFML/Graphics.hpp>
#include "Const.h"
//pressend the data of the game

class GameData
{
public:
	GameData();
	void display(sf::RenderWindow& );
	void updateData(int, int, int, sf::Time deltaTime);
	void setPosition( float boardHeight);
	int getHeight() const; 
	bool isTimeUp() const; 
	void reset();
private:
	sf::Text m_text;
	sf::Text m_timer;
	float m_timeLeft;
};
