
#include "Moving.h"
#include <cmath>
#include "Controller.h"

Moving::Moving(const sf::Vector2f& position, const sf::Texture& texture, float speed)
    : Object(position, texture), m_direction({ 0.f,0.f }), m_speedPerSecond(speed),
    m_startingPos(position), m_velocity({ 0.f, 0.f }), m_applyGravity(true), m_onLadder(false), m_onPole(false)
{ }

void Moving::setPosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
    m_velocity = { 0.f, 0.f }; 
}

sf::Vector2f Moving::getPosition() const
{
    return m_sprite.getPosition();
}

void Moving::setStartingPos(const sf::Vector2f& position)
{
    m_startingPos = position;
}

void Moving::stopVelocityY()
{
    m_velocity.y = 0;
}

void Moving::stopVelocityX()
{
    m_velocity.x = 0;
}

bool Moving::holeBetweenFloor(Controller& controller)//edge case
{
    sf::FloatRect myBounds = getGlobalBounds();
    sf::Vector2f center = myBounds.position + (myBounds.size / 2.f);

    int row = static_cast<int>(center.y / PANEL_SIZE);
    int col = static_cast<int>(center.x / PANEL_SIZE);

    //need to check the tiles below are: "# #"
    bool leftBlock = controller.getTileChar(row + 1, col - 1) == FLOOR;
    bool rightBlock = controller.getTileChar(row + 1, col + 1) == FLOOR;
    bool centerHole = controller.getTileChar(row + 1, col) == EMPTY;

    if (leftBlock && rightBlock && centerHole)
    {
        //build the rectangle:
        sf::Vector2f holePos(static_cast<float>(col * PANEL_SIZE), static_cast<float>((row + 1) * PANEL_SIZE));
        sf::Vector2f holeSize(static_cast<float>(PANEL_SIZE), static_cast<float>(PANEL_SIZE));

        sf::FloatRect holeRect(holePos, holeSize);

        falling(holeRect); //do the same think we did with the ground function
        return true;
    }
    return false;
}

void Moving::resolveBlockingCollision(const sf::FloatRect& blockRect) 
{
    sf::FloatRect myRect = getGlobalBounds();
    auto intersection = myRect.findIntersection(blockRect);

    if (!intersection) return;

    sf::FloatRect overlap = *intersection;

    if (overlap.size.x > overlap.size.y - 2.f)
    {
        if (myRect.position.y < blockRect.position.y)
        {
            //stand above floor
            setPosition({ getPosition().x, blockRect.position.y - myRect.size.y });
            stopVelocityY(); //stop falling
        }
        else
        {
            //below floor
            setPosition({ getPosition().x, blockRect.position.y + blockRect.size.y });
            stopVelocityY();
        }
    }
    else //its a wall
    {
        if (myRect.position.x < blockRect.position.x)
            setPosition({ blockRect.position.x - myRect.size.x, getPosition().y });
        else
            setPosition({ blockRect.position.x + blockRect.size.x, getPosition().y });
    }
}

void Moving::move(sf::Time deltaTime) {
    handleDirection(); // update m_direction
    
    m_velocity.x = m_direction.x * m_speedPerSecond;

    //if on ladder or pole:
    if (!m_applyGravity) {
        m_velocity.y = m_direction.y * m_speedPerSecond;
    }
    else {
        m_velocity.y += GRAVITY * deltaTime.asSeconds();
        
    }

    m_sprite.move(m_velocity * deltaTime.asSeconds());
    if (m_velocity.y > 250.0f)
    {
        m_velocity.y = 250.0f; //dont fall too fast
    }

    m_onLadder = false;
    m_onPole = false;
    m_applyGravity = true;
}

void Moving::falling(const sf::FloatRect& holeBounds)
{
    m_applyGravity = true; //fall in the hole

    sf::FloatRect myBounds = getGlobalBounds();

    // snap the player's location to the middle of the hole:
    float targetX = holeBounds.position.x + (holeBounds.size.x - myBounds.size.x) / 2.0f;
    float currentX = getPosition().x;
    float diff = std::abs(currentX - targetX);



    if (diff < SNAP_TOLERANCE)//make sure the moving object will fall
    {
        setPosition({ targetX, getPosition().y });

        m_velocity.x = 0;
        m_direction.x = 0;
        if (m_velocity.y < 250.0f)
        {
            m_velocity.y = 250.0f;
        }
    }
}

void Moving::handleBoardEdges(const sf::Vector2f& pos, float boardWidth)
{
    //the corners:
    if (pos.x < 0)
        setPosition({ 0, pos.y });

    else if (pos.x > boardWidth * PANEL_SIZE - PANEL_SIZE)
        setPosition({ boardWidth * PANEL_SIZE - PANEL_SIZE , pos.y });
    //dont go up:
    if (pos.y < 0)
    {
        setPosition({ pos.x, 0 });
        stopVelocityY();
    }
}