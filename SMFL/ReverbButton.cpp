#include "stdafx.h"
#include "ReverbButton.h"
#include "SoundManager.h"


ReverbButton::ReverbButton(sf::IntRect p_position)
{
	m_font.loadFromFile("C:\\Windows\\Fonts\\consolaz.TTF");
	m_text.setFont(m_font);
	m_background = sf::RectangleShape();
	m_background.setPosition(sf::Vector2f(p_position.left, p_position.top));
	m_background.setSize(sf::Vector2f(p_position.width, p_position.height));
	m_background.setFillColor(sf::Color::Blue);
	m_rect = p_position;
	m_isReverbEnabled = false;
	m_text.setPosition(m_rect.left + m_rect.width / 6, m_rect.top + m_rect.height / 4);
	m_text.setCharacterSize(12);
	m_circle.setRadius(150);
	m_circle.setPosition(sf::Vector2f(150, 250));
	m_circle.setOutlineColor(sf::Color::Black);
	m_circle.setOutlineThickness(5);
	m_circle.setFillColor(sf::Color::Transparent);
}


ReverbButton::~ReverbButton()
{

}



void ReverbButton::Update(sf::Vector2i p_mousePos)
{
	bool collidingX = (p_mousePos.x > m_rect.left && p_mousePos.x < m_rect.left + m_rect.width);
	bool collidingY = (p_mousePos.y > m_rect.top && p_mousePos.y < m_rect.top + m_rect.height);

	if (collidingX && collidingY)
		ClickedFunc();

	m_text.setPosition(m_rect.left + m_rect.width / 6, m_rect.top + m_rect.height / 4);
}

void ReverbButton::ClickedFunc()
{
	m_isReverbEnabled = !m_isReverbEnabled;
	SoundManager::Instance().reverb->setActive(m_isReverbEnabled);
}

void ReverbButton::Draw(sf::RenderWindow &p_window)
{
	if (m_isReverbEnabled)
		m_text.setString("Reverb is Enabled!");
	else
		m_text.setString("Reverb is Disabled!");

	p_window.draw(m_background);
	p_window.draw(m_text);

	if (m_isReverbEnabled)
		p_window.draw(m_circle);
}
