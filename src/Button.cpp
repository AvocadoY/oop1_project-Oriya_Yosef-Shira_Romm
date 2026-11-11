#include "Button.h"
#include "ResourceManager.h"

Button::Button(const std::string& textStr, const sf::Vector2f& position):m_text(ResourceManager::getInstance().getFont()),
m_normalColor(sf::Color::White),  m_hoverColor( sf::Color::Yellow),
m_hoverSound(ResourceManager::getInstance().getSound(ResourceManager::S_Hover))
{
    m_text.setString(textStr);
    m_text.setCharacterSize(40);
    m_text.setPosition(position);
    m_text.setFillColor(m_normalColor);
    m_hoverSound.setVolume(50); 
}

void Button::draw(sf::RenderWindow& window) const
{
    window.draw(m_text);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const
{
    //get the mouse location
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    //check if the mouse is in the current button
    return m_text.getGlobalBounds().contains(mousePosF);
}

//this function update the color and the sound of the button acording to its state
void Button::update(const sf::RenderWindow& window)
{
    if (isMouseOver(window))
    {
        m_text.setFillColor(m_hoverColor);
        m_hoverSound.play();
    }
    else
    {
        m_text.setFillColor(m_normalColor);
    }
}