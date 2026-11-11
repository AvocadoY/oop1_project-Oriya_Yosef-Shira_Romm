
#include "ResourceManager.h"
#include "Menu.h"
#include "Const.h"

Menu::Menu(int width,int height) :m_btnNewGame("New Game", sf::Vector2f((width / 2)-40.f, height * 0.4f)),
m_btnHelp("Help", sf::Vector2f((width / 2)-40.f, height * 0.55f)), m_btnExit("Exit", sf::Vector2f((width / 2)-40.f, height * 0.7f)), m_width(width), m_height(height),
m_photo(ResourceManager::getInstance().getTexture(ResourceManager::MenuPhoto))
{
    m_photo.setColor(sf::Color(255, 255, 255, 50));
}

void Menu::createWindow(sf::RenderWindow& window) const
{
	window.create(sf::VideoMode({ m_width, m_height }), "Menu");
}

MenuAction Menu::run(sf::RenderWindow& window) //returns the button the controller need to know about
{
    while (window.isOpen())
    {
        ResourceManager::getInstance().playMusic(ResourceManager::M_Menu);
        m_btnNewGame.update(window);
        m_btnHelp.update(window);
        m_btnExit.update(window);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                return MenuAction::Exit;
            }

            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseBtn->button == sf::Mouse::Button::Left)
                {
                    if (m_btnNewGame.isMouseOver(window)) return MenuAction::NewGame;
                    if (m_btnHelp.isMouseOver(window)) showHelp(window); //no need to return to the controller
                    if (m_btnExit.isMouseOver(window))    return MenuAction::Exit;
                }
            }
        }
        window.clear(DEEP_PINK);
        window.draw(m_photo);
        m_btnNewGame.draw(window);
        m_btnHelp.draw(window);
        m_btnExit.draw(window);
        window.display();
    }
    return MenuAction::Exit;
}

void Menu::showHelp(sf::RenderWindow& window) const
{
    sf::Text helpText(ResourceManager::getInstance().getFont());
    helpText.setString("Game Instructions:\n\n"
        "Move: Arrow Keys\n"
        "Dig Left: Z\n"
        "Dig Right: X\n"
        "Goal: Collect all coins to win!\n\n"
        "Press ESC to return");
    helpText.setCharacterSize(30);
    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return;
            }
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyEvent->code == sf::Keyboard::Key::Escape)
                {
                    return; //go back to run
                }
            }
        }
       


        window.clear(sf::Color(50, 50, 50)); 
        window.draw(helpText);
        window.display();
    }
}