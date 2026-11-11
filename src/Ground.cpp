#include "Ground.h"
#include "ResourceManager.h"
#include "Digging.h"

Ground::Ground(const sf::Vector2f& position, const sf::Texture& texture):Standing(position, texture) ,m_isHole(false)
{ }

void Ground::dig()
{
    //the ground is now hole- start counting the time before its closed
    m_isHole = true;
    m_timer.restart();

    m_sprite.setColor(sf::Color(255, 255, 255, 0)); // transperent
}

void Ground::checkTime() 
{
    if (m_isHole)
    {
        // times up
        if (m_timer.getElapsedTime().asSeconds() > HOLE_TIME)
        {
            
            m_isHole = false;

            m_sprite.setColor(sf::Color::White);
        }
    }
}

bool Ground::isHole() const
{
    return m_isHole;
}

void Ground::handleCollision(Digging& digging) //with the digging class we can go to the current dig land
{
    dig();
    digging.handleCollision(*this);
}