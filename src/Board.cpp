#include "Board.h"
#include "Digging.h"

Board::Board()
{
    m_background.setFillColor(BACKGROUND_COLOR);
}

void Board::draw(sf::RenderWindow& window) const
{
    window.draw(m_background);
    for (int i=0;i<m_landscape.size();i++)
    {
        m_landscape[i]->draw(window); 
        
    }
    for (int i = 0;i < m_coins.size();i++)
    {
        m_coins[i].draw(window);
    }
}

unsigned int Board::getRows() const
{
    return m_originalMap.size();
}

unsigned int Board::getCols() const
{
    return m_originalMap[0].size();
}

void Board::checkCollision(Moving& mov)
{
    for (size_t i = 0; i < m_landscape.size(); i++)
    {
        if (mov.checkCollision(*m_landscape[i]))
        {
            m_landscape[i]->handleCollision(mov);
        }
    }
    
    for (auto& coin : m_coins)
    {
        if (!coin.isTaken() && mov.checkCollision(coin))
        {
            coin.handleCollision(mov); 
        }
    }

    std::erase_if(m_coins, [](const Coin& coin) {
        return coin.isTaken();
        });
}

bool Board::nextLevel() const
{
    return m_coins.size() == 0; //the player took all the coins in the level?
}

//read the file to the matrix
std::vector<Enemy> Board::loadFromFile(const std::string& fileName, Player& player, Controller& controller)
{
    m_originalMap.clear();
    std::ifstream inFile(fileName);

    if (!inFile)
    {
        throw std::runtime_error("Cannot open level file");
    }

    //size
    int rows, cols;
    inFile >> rows >> cols;
    m_background.setSize({ 1.0f * cols * PANEL_SIZE, 1.0f * rows * PANEL_SIZE });

    inFile.get(); //for the new line

    std::string line;
    while (std::getline(inFile, line))
    {
        m_originalMap.push_back(line); //save the line
    }

    inFile.close(); //dont with this file

    return resetBoard(player, controller);
}

std::vector<Enemy> Board::resetBoard(Player& player, Controller& controller)
{
    m_landscape.clear(); 
    m_holes.clear();
    m_coins.clear();
    std::vector<Enemy> foundEnemies; 
    auto& res = ResourceManager::getInstance();

    for (int i = 0; i < getRows(); ++i)
    {
        if (i >= m_originalMap.size()) break;

        for (int j = 0; j < getCols(); ++j)
        {
            if (j >= m_originalMap[i].size()) break;
            
            char c = m_originalMap[i][j];
            sf::Vector2f pos(j * PANEL_SIZE, i * PANEL_SIZE);

            switch (c) {
            case ENEMY: 
                foundEnemies.push_back(Enemy(pos, res.getTexture(ResourceManager::Enemy), controller));
                break;
            case PLAYER:
                player.setPosition(pos); 
                player.setStartingPos(pos);
                break;
            case FLOOR:
                m_landscape.push_back(std::make_unique<Floor>(pos, res.getTexture(ResourceManager::Floor)));
                break;
            case LADDER:
                m_landscape.push_back(std::make_unique<Ladder>(pos, res.getTexture(ResourceManager::Ladder)));
                break;
            case POLE:
                m_landscape.push_back(std::make_unique<Pole>(pos, res.getTexture(ResourceManager::Pole)));
                break;
            case GROUND:
                m_landscape.push_back(std::make_unique<Ground>(pos, res.getTexture(ResourceManager::Ground)));
                break;
            case COIN: 
            {
                auto coin = Coin(pos, res.getTexture(ResourceManager::Coin));
                m_coins.push_back(coin);
                break;
            }
            default:
                break;
            }
        }
    
    }
    return foundEnemies; //return the enemies vector to the controller
}

char Board::getCharAt(int row, int col) const
{
    if (row < 0 || row >= m_originalMap.size()) return FLOOR; //out of bounds-floor
    if (col < 0 || col >= m_originalMap[row].size()) return FLOOR;

    return m_originalMap[row][col];
}

void Board::tryDig(const sf::Vector2f& targetPos)
{
    //for checking the ground that the player dig . the Digging class help to enter new ground to the vector isHole. 
    //acording to the possition we try to dig
    Digging digging(targetPos, this);
    for (size_t i = 0; i < m_landscape.size(); i++)
    {
        if (digging.checkCollision(*m_landscape[i])) 
        {
            digging.handleCollision(*m_landscape[i]);
        }
    }
}
    
void Board::update()//this function update the grounds the player dig. 
{
    for (size_t i = 0; i < m_holes.size(); i++)
    {
        auto* ground = static_cast<Ground*>(m_holes[i]);
        //all the grounds in isHole check if its time to fill
        ground->checkTime();
    }

    std::erase_if(m_holes, [](const auto* ground) { return !ground->isHole(); });
}

void Board::addHole(Ground& ground) 
{
    m_holes.push_back(&ground);
}