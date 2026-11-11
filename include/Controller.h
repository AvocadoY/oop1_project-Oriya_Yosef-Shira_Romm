#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Menu.h"
#include "Enemy.h"
#include "Board.h"
#include "Player.h"
#include "Ladder.h"
#include "Floor.h"
#include "Coin.h"
#include "ResourceManager.h"
#include "GameData.h"

class Controller
{
public:	
	Controller();
	void run();
	sf::Vector2f getPlayerPosition() const;
	char getTileChar(int,int) const;
	int getBoardCols() const;
	int getLevel() const;
	void tryDig(const sf::Vector2f& targetPos);	
private:
	
	sf::RenderWindow m_window;
	int m_level;
	std::vector <Enemy> m_enemies;
	Menu m_menu;
	Player m_player;
	Board m_board;
	sf::Clock m_timer;
	std::vector<std::string> m_levelFiles;
	GameData m_gameData;
	sf::Sound m_newLevelSound;
	sf::Sound m_loseSound;

	void handle(const auto&) { /* ignore other events */ }
	void handle(const sf::Event::Closed&);
	void loadLevel(); 
	void handleCollisions();
	void resetLevel();
	void initGame();
	void timesUp();
	void createWindow();
	void checkOutOfBound();
	void playGame();
	void showWinLoseScreen(const std::string& string);
};