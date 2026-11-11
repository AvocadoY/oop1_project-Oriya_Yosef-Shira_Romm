#include "Controller.h"
#include <iostream>

Controller::Controller(): m_player(*this), m_board(), m_gameData(),m_menu(800,600) ,
m_newLevelSound(ResourceManager::getInstance().getSound(ResourceManager::S_LevelUp)),
	m_loseSound(ResourceManager::getInstance().getSound(ResourceManager::S_Lose))
{
	m_newLevelSound.setVolume(60);
	m_loseSound.setVolume(60);
	m_level = 1;
	//read the levels name in the game:
	std::ifstream playlistFile("Board.txt"); 
	std::string line;
	while (std::getline(playlistFile, line)) {
		m_levelFiles.push_back(line);
	}
	
}

void Controller::run()
{
	m_menu.createWindow(m_window);
	bool menuOpened = true;
	ResourceManager::getInstance().playMusic(ResourceManager::M_Menu);
	while (m_window.isOpen())
	{
		if(!menuOpened) 
			m_menu.createWindow(m_window); //the game starts in the menu
		ResourceManager::getInstance().playMusic(ResourceManager::M_Game);

		auto action = m_menu.run(m_window);

		//check the action the controller need to do from the user
		if (action == MenuAction::Exit)
		{
			m_window.close();
		}
		else if (action == MenuAction::NewGame)
		{
			initGame(); 
			createWindow();
			playGame(); 
			//when playGame is done, this loop show the menu again
		}
		menuOpened = false;
	}
}

void Controller::playGame()
{
	ResourceManager::getInstance().playMusic(ResourceManager::M_Game);
	m_timer.restart(); 

	while (m_window.isOpen())
	{
		m_window.clear();
		//draw:
		m_board.draw(m_window);
		m_player.draw(m_window);
		for (int i = 0;i < m_enemies.size();i++)
		{
			m_enemies[i].draw(m_window);
		}
		m_gameData.display(m_window);
		m_window.display();

		// Causing Address Sanitizer failure due to system bug (approved by Yehezkel)
		//m_window.handleEvents([this](const auto& event) { handle(event); });
		while (const std::optional event = m_window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				handle(*event->getIf<sf::Event::Closed>());
				return;
			}
			
		}
		m_player.handleInput(); 
		sf::Time dt = m_timer.restart();
		m_gameData.updateData(m_level, m_player.getScore(), m_player.getLifes(),dt);
		//move:
		m_player.move(dt);
		for (auto& enemy : m_enemies) {
			enemy.move(dt);
		}

		handleCollisions();

		m_board.update(); //for the ground the we dig
		
		
		checkOutOfBound();
		if (m_player.getLifes()<=0) //dead
		{
			m_loseSound.play();
			showWinLoseScreen("YOU LOST!");
			
			return;//call the menu
		}
		if (m_board.nextLevel())
		{
			m_newLevelSound.play();
			m_player.newLevel();
			m_level++;
			if (m_level <= m_levelFiles.size())
			{
				loadLevel();
				createWindow();
			} 
			else if (m_level > m_levelFiles.size()) //end of the game
			{
				showWinLoseScreen("YOU WON!");
				return; ///call the menu
			}
		}
		if (m_gameData.isTimeUp())
		{
			m_player.timesUp();
			timesUp();
		}

	}
}

void Controller::handle(const sf::Event::Closed&)
{
	m_window.close();
}

void Controller::loadLevel()
{
	m_enemies.clear();
	std::string fileName = m_levelFiles[m_level-1]; // for example: "Level1.txt"

	m_enemies = m_board.loadFromFile(fileName, m_player,*this); //update the player location and the enemies vector
	m_gameData.reset();
	
}

void Controller::createWindow()
{
	m_gameData.setPosition(m_board.getRows()*PANEL_SIZE);
	m_window.create(sf::VideoMode({ m_board.getCols() * PANEL_SIZE 
			,m_board.getRows() * PANEL_SIZE + m_gameData.getHeight()}), "Birthday Runner");
	m_window.setFramerateLimit(60);
	m_timer.restart();
}

//for the enemy's help:
sf::Vector2f Controller::getPlayerPosition() const
{
	return m_player.getPosition();
}

int Controller::getBoardCols() const
{
	return m_board.getCols();
}

void Controller::handleCollisions() {
	
	m_board.checkCollision(m_player);

	for (auto& enemy : m_enemies)
	{
		m_board.checkCollision(enemy);
	}

	//the controller is cheking the player vs enemy
	for (auto& enemy : m_enemies) {
		if (m_player.checkCollision(enemy)) {
			m_player.handleCollision(enemy);
			resetLevel();
			break;
		}
	}
}

//all the enemies to their starting position
void Controller::resetLevel()
{
	for (int i = 0;i < m_enemies.size();i++)
		m_enemies[i].handleCollision(m_player);
}

void Controller::initGame()
{      
	m_level = 1;
	m_player.init(); //score =0
	loadLevel(); //load first level
	
}

//times up function
void Controller::timesUp()
{
	//retet all objects that can reset
	m_board.resetBoard(m_player,*this);
	
	m_timer.restart();
}

//for the player's help:
int Controller::getLevel() const
{
	return m_level;
}

char Controller::getTileChar(int row,int col) const
{
	return m_board.getCharAt(row,col); //ask the board
}

void Controller::tryDig(const sf::Vector2f& targetPos)
{
	m_board.tryDig(targetPos);
}

void Controller::checkOutOfBound()
{
	m_player.checkOutOfBound(m_board.getCols(),m_board.getRows());
	for (int i = 0;i < m_enemies.size();i++)
		m_enemies[i].checkOutOfBound(m_board.getCols(),m_board.getRows());
}

void Controller::showWinLoseScreen(const std::string& string)
{
	
	sf::Text winText(ResourceManager::getInstance().getFont());
	
	winText.setString(string); 
	winText.setCharacterSize(80);  
	winText.setFillColor(sf::Color::White); 

	while (m_window.isOpen())
	{
		
		while (const std::optional event = m_window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				handle(*event->getIf<sf::Event::Closed>());
				return;
			}

			//if any key got pressed- exit the function
			if (event->is<sf::Event::KeyPressed>() || event->is<sf::Event::MouseButtonPressed>())
			{
				return; 
			}
		}

		//draw:
		m_window.clear(sf::Color::Color(DEEP_PINK)); 
		m_window.draw(winText);          
		m_window.display();               
	}
}