#pragma once
#include <SFML/Graphics.hpp>
#include "Standing.h"

class Floor : public Standing
{
public:
	using Standing ::Standing;
	void handleCollision(Object& object) override; 
};