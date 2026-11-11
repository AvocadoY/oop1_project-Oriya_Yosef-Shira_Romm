#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

enum class MenuAction {
	None,
	NewGame,
	Help,
	Exit
};
class Menu
{
public:
	Menu(int,int);
	MenuAction run(sf::RenderWindow&);
	void createWindow(sf::RenderWindow&) const;
private:
	Button m_btnNewGame;
	Button m_btnHelp;
	Button m_btnExit;
	unsigned int m_width;
	unsigned int m_height;
	sf::Sprite m_photo;
	void showHelp(sf::RenderWindow& window) const;
};