#include "GameData.h"
#include "ResourceManager.h"
#include <string>

GameData::GameData(): m_timer(ResourceManager::getInstance().getFont()), m_text(ResourceManager::getInstance().getFont()),m_timeLeft(GAME_TIME)
{
	m_timer.setString("");
	m_timer.setCharacterSize(TEXT_SIZE);
	m_text.setString("");
	m_text.setCharacterSize(TEXT_SIZE);
}

void GameData::display(sf::RenderWindow& window)
{
	window.draw(m_timer);
	window.draw(m_text);
}

void GameData::updateData(int level,int score,int lifes, sf::Time deltaTime)
{
	std::string data= "Level: " + std::to_string(level) + " Score: " + std::to_string(score) + " Lifes: " + std::to_string(lifes);
	m_text.setString(data);

	m_timeLeft -= deltaTime.asSeconds();
	if (m_timeLeft < 0) m_timeLeft = 0;

	int minutes = (int)m_timeLeft / 60;
	int seconds = (int)m_timeLeft % 60;

	//write the timer:
	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << minutes << ":"
		<< std::setw(2) << std::setfill('0') << seconds;

	m_timer.setString(ss.str());
}

void GameData::setPosition(float boardHeight)
{
	// below boardHeight
	float barY = boardHeight + 10.f; 

	m_text.setPosition({10.f, barY});
}

void GameData::reset()
{
	m_timeLeft=GAME_TIME;
}

int GameData::getHeight() const 
{
	return 50;
}

bool GameData::isTimeUp() const //return for the controller the acurate timer the user sees
{ 
	return m_timeLeft <= 0; 
}