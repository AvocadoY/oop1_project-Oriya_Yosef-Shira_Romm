#pragma once
#include <vector>
#include <string>
#include "Standing.h"
#include "ResourceManager.h"
#include <fstream>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Pole.h"
#include "Ladder.h"
#include "Ground.h"
#include "Floor.h"

class Board
{
public:
    Board();
    void draw(sf::RenderWindow&) const;
    unsigned int getCols() const;
    unsigned int getRows() const;
    //size_t size() const { return m_landscape.size(); }
    void checkCollision(Moving& mov);
    bool nextLevel() const;
    std::vector<Enemy> loadFromFile(const std::string& fileName, Player& player, Controller& controller);
    std::vector<Enemy> resetBoard(Player& player, Controller& controller);
    char getCharAt(int,int) const;
    void tryDig(const sf::Vector2f& targetPos);
    void update();
    void addHole(Ground& ground);
private:
    std::vector<std::unique_ptr<Standing>> m_landscape;
    std::vector <Coin> m_coins;
    std::vector<std::string> m_originalMap;
    sf::RectangleShape m_background;
    std::vector<Ground*> m_holes;
};

