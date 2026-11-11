#include "Player.h"
#include "Enemy.h"
#include "Controller.h"


Player::Player(Controller & controller): Moving(sf::Vector2f(0,0),
    ResourceManager::getInstance().getTexture(ResourceManager::Player),PLAYER_SPEED), m_controller(controller),
    m_enemySound(ResourceManager::getInstance().getSound(ResourceManager::S_Enemy)),m_coinSound(ResourceManager::getInstance().getSound(ResourceManager::S_Coin)),
    m_shovelSound(ResourceManager::getInstance().getSound(ResourceManager::S_Dig))
{
    m_shovelSound.setVolume(60);
    m_enemySound.setVolume(50);
    m_coinSound.setVolume(50);
    init();
}

void Player::handleDirection()
{
    m_direction = { 0, 0 };
    m_applyGravity = true; 

    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    float playerWidth = bounds.size.x;  
    float playerHeight = bounds.size.y; 
    sf::Vector2f pos = getPosition();   

    //the center of the player
    sf::Vector2f centerPos = pos;
    centerPos.x += playerWidth / 2.0f;
    centerPos.y += playerHeight / 2.0f;

    int row = static_cast<int>(centerPos.y / PANEL_SIZE);
    int col = static_cast<int>(centerPos.x / PANEL_SIZE);

    char currentTile = m_controller.getTileChar(row, col);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        m_direction = LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        m_direction = RIGHT;
    }

    
    float tileCenterX = (col * PANEL_SIZE) + (PANEL_SIZE / 2.0f);
    float diff = std::abs(centerPos.x - tileCenterX);

    //make sure we are on the ladder:
    bool physicallyOnLadder = (currentTile == LADDER);

    if (m_onLadder && physicallyOnLadder)
    {
        m_applyGravity = false; 

        //can go up and down:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            if (diff < SNAP_TOLERANCE)
            {
                m_direction = UP;
                //snap to the middle
                sf::Vector2f newPos = getPosition();
                newPos.x = tileCenterX - (playerWidth / 2.0f);
                setPosition(newPos);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            if (diff < SNAP_TOLERANCE)
            {
                m_direction = DOWN;
               
                sf::Vector2f newPos = getPosition();
                newPos.x = tileCenterX - (playerWidth / 2.0f);
                setPosition(newPos);
            }
        }
    }
    // pole
    else if (m_onPole && currentTile == POLE)
    {
        m_applyGravity = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            //m_onPole = false;
            m_applyGravity = true; 
        }
    }

    m_onLadder = false;
    m_onPole = false;
}

void Player::handleCollision(Object& other)
{
    other.handleCollision(*this);
}

void Player::handleCollision(Floor& floor)
{
    m_velocity.y = 0;
    if(!holeBetweenFloor(m_controller))
        resolveBlockingCollision(floor.getGlobalBounds());
}

void Player::handleCollision(Coin& coin) 
{
    int level=m_controller.getLevel();
    m_score += 2*level;
    m_coinSound.play();
    coin.handleCollision(*this);
}

void Player::handleCollision(Enemy& enemy)
{
    m_lifes--;
    setPosition(m_startingPos);
    m_enemySound.play();
}

int Player::getLifes() const
{
    return m_lifes;
}

int Player::getScore() const
{
    return m_score;
}

void Player::init()
{
    m_lifes = LIFES;  //reset life and score
    m_score = 0;  
    m_velocity = { 0, 0 };
}

void Player::newLevel()
{
    int level = m_controller.getLevel();
    m_score += 50 * level;
}

void Player::handleInput()//for the digging
{ 
    sf::Vector2f myPos = getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    {
        m_shovelSound.play();
        m_controller.tryDig(sf::Vector2f(myPos.x - PANEL_SIZE, myPos.y + PANEL_SIZE)); // dig to left
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
    {
        m_shovelSound.play();
        m_controller.tryDig(sf::Vector2f(myPos.x + PANEL_SIZE, myPos.y + PANEL_SIZE)); //dig to right
    }
}

void Player::handleCollision(Ground& ground)
{
    if (ground.isHole())
    {
        falling(ground.getGlobalBounds());//make sure the player is falling into the hole

        return; 
    }
    //if the ground is floor:
    resolveBlockingCollision(ground.getGlobalBounds());
    
}

void Player::checkOutOfBound(float boardWidth, float boardHeight)
{
    
    sf::Vector2f pos = getPosition();

    // fall- decrease lifes
    if (pos.y > boardHeight*PANEL_SIZE)
    {
        m_lifes--;
        setPosition(m_startingPos);
    }
    handleBoardEdges(pos, boardWidth);
}

void Player::handleCollision(Pole& pole)
{
    m_onPole = true;
}

void Player::handleCollision(Ladder& ladder)
{

    m_onLadder = true; 
}

void Player::timesUp()
{
    m_lifes--;
}
