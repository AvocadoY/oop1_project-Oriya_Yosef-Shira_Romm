#pragma once

#include "Object.h"

//this function help the ground that the player digged
class Board;

class Digging : public Object
{
public:
	Digging(const sf::Vector2f position, Board* board);
	
	void handleCollision(Object& other) override;
	void handleCollision(Ground& ground) override;

private:
	Board* m_board;
};