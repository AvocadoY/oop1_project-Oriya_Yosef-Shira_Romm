#include "Pole.h"

void Pole::handleCollision(Object& object) 
{ 
	object.handleCollision(*this);
}
