#pragma once
#include <SFML/Graphics.hpp>
#include "Standing.h"

class Ladder : public Standing
{
public:
	using Standing::Standing;
	//ResourceManager::Type getType() const  { return ResourceManager::Ladder; }
	void handleCollision(Object& object) override; 
};