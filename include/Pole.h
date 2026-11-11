#pragma once
#include <SFML/Graphics.hpp>
#include "Standing.h"

class Pole : public Standing
{
public:
	using Standing::Standing;
	void handleCollision(Object& object) override; 
};