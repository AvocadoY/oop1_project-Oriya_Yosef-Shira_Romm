#include <Floor.h>

void Floor::handleCollision(Object & object)
{
	object.handleCollision(*this); 
}