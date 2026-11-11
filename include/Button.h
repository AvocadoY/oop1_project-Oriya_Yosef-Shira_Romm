#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
//this class show the buttons in the menu
class Button
{
public:
    Button(const std::string& text, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window) const;
    bool isMouseOver(const sf::RenderWindow& window) const;

    void update(const sf::RenderWindow& window);

private:
    sf::Text m_text;
    sf::Color m_normalColor;
    sf::Color m_hoverColor;
    sf::Sound m_hoverSound;
};