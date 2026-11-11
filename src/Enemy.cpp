#include "Enemy.h"
#include "Controller.h" 
#include <cmath>
#include <iostream>

Enemy::Enemy(const sf::Vector2f& position, const sf::Texture& texture,Controller &controller) :Moving(position, texture, ENEMY_SPEED), 
m_controller(controller),m_trapped(false)
{
  
}

void Enemy::handleCollision(Floor& floor)
{
    if(!holeBetweenFloor(m_controller))
        resolveBlockingCollision(floor.getGlobalBounds());
}

void Enemy::handleCollision(Player& player)
{
    setPosition(m_startingPos);
}

void Enemy::handleCollision(Object& object)  
{
    object.handleCollision(*this); 
}

void Enemy::handleCollision(Ground& ground)
{
    if (ground.isHole())
    {
        m_trapped = true;
        falling(ground.getGlobalBounds());

        return;
    }
    //if the ground is floor:
    m_trapped = false;
    resolveBlockingCollision(ground.getGlobalBounds());
}

void Enemy::handleCollision(Pole& pole)
{
    m_onPole = true;
}

void Enemy::handleCollision(Ladder& ladder)
{
    m_onLadder = true; 
}

void Enemy::checkOutOfBound(float boardWidth, float boardHeight)
{

    sf::Vector2f pos = getPosition();

    if (pos.y > boardHeight*PANEL_SIZE)
    {
        setPosition(m_startingPos); //fall out of bounds- return to the starting pos
        
    }
    //attach to the window's edges
    handleBoardEdges(pos, boardWidth);
}

void Enemy::handleDirection()
{
    if (m_trapped) //if the enemy is in the hole- make sure he is falling
    {
        m_direction = { 0, 0 };
        m_applyGravity = true;
        m_onLadder = false;
        m_onPole = false;
        m_trapped = false;
        return ;
    }

    sf::Vector2f myPos = getPosition();
    sf::Vector2f playerPos = m_controller.getPlayerPosition();

    int myRow = (int)(myPos.y + PANEL_SIZE / 2) / PANEL_SIZE;
    int myCol = (int)(myPos.x + PANEL_SIZE / 2) / PANEL_SIZE;
    int pRow = (int)(playerPos.y + PANEL_SIZE / 2) / PANEL_SIZE;
    int pCol = (int)(playerPos.x + PANEL_SIZE / 2) / PANEL_SIZE;

    m_direction = { 0, 0 };


    //the enemy and the player in the same row
    if (myRow == pRow)
    {
        float targetX = myCol * PANEL_SIZE;
        float targetY = myRow * PANEL_SIZE;
        if (std::abs(myPos.y - targetY) > 2.0f)
        {
            // move until you in the exact middle
            if (myPos.y > targetY) m_direction = UP;
            else                   m_direction = DOWN;

            m_sprite.setPosition({ targetX, myPos.y });
        }
        else
        {
            //exacly the right height
            m_sprite.setPosition({ myPos.x, targetY });
            //where to turn
            if (pCol > myCol) m_direction = RIGHT;
            else if (pCol < myCol) m_direction = LEFT;
        }
    }
    else
    {
        //find the best ladder
        int targetCol = getBestColumn(myRow, myCol, pRow);
        float destX = targetCol * PANEL_SIZE;

        if (std::abs(myPos.x - destX) > 5.0f)//snap the enemy to the middle of the fanel
        {
            if (myPos.x < destX) m_direction = RIGHT;
            else                 m_direction = LEFT;
        }
        else
        {
            m_sprite.setPosition({ destX, myPos.y });

            if (pRow < myRow)      m_direction = UP;
            else if (pRow > myRow) m_direction = DOWN;
        }
    }

    //  handle the gravity
    char currentTile = m_controller.getTileChar(myRow, myCol);

    if (m_onPole && m_direction == DOWN) return ;
    if(m_onLadder && m_direction.y != 0)
    {
        m_applyGravity = false; 
    }

    else if (currentTile == POLE)
    {
        //m_onPole = true;
        m_applyGravity = false;
        //snap to the middle of the pole
        float targetY = myRow * PANEL_SIZE;
        if (std::abs(myPos.y - targetY) < 5.0f)
        {
            m_sprite.setPosition({ myPos.x, targetY });
        }
    }

}

//this function returns the best col the enemy can go 
int Enemy::getBestColumn(int myRow, int myCol, int playerRow)
{
    int bestCol = -1;
    int minDistance = 9999;
    int cols = m_controller.getBoardCols(); 

    bool lookUp = (playerRow < myRow); //is the player above the enemy?

    
    for (int c = 0; c < cols; ++c)//go through all the columns
    {
        char currentTile = m_controller.getTileChar(myRow, c);

        bool isValid = false;

        if (lookUp)
        {
            char tileAbove = m_controller.getTileChar(myRow - 1, c);

            // if the enemy on the latter- clime
            if (currentTile == LADDER && tileAbove == LADDER)
            {
                isValid = true;
            }
        }
        else 
        {
            char tileBelow = m_controller.getTileChar(myRow + 1, c);

            if (currentTile == LADDER && tileBelow == LADDER) isValid = true;
        }

        if (isValid)
        {
            int dist = std::abs(c - myCol);
            if (dist < minDistance)
            {
                minDistance = dist;
                bestCol = c;
            }
        }
    }

    if (bestCol == -1) return myCol;

    return bestCol;
}
