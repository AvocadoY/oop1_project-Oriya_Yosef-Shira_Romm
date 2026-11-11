#include "Ladder.h"

void Ladder::handleCollision(Object& object)  
{ 
	object.handleCollision(*this); 
}
