#include "stdafx.h"
#include "PauseSoundButton.h"
#include "SoundManager.h"


PauseSoundButton::PauseSoundButton(sf::IntRect p_position)
{
	m_font.loadFromFile("C:\\Windows\\Fonts\\consolaz.TTF");
	m_text.setFont(m_font);
	m_background = sf::RectangleShape();
	m_background.setPosition(sf::Vector2f(p_position.left, p_position.top));
	m_background.setSize(sf::Vector2f(p_position.width, p_position.height));
	m_background.setFillColor(sf::Color::Blue);
	m_rect = p_position;
	m_isSoundEnabled = false;
	m_text.setPosition(m_rect.left + m_rect.width / 6, m_rect.top + m_rect.height / 4);
	m_text.setCharacterSize(12);
}


PauseSoundButton::~PauseSoundButton()
{

}



void PauseSoundButton::Update(sf::Vector2i p_mousePos)
{
	bool collidingX = (p_mousePos.x > m_rect.left && p_mousePos.x < m_rect.left + m_rect.width);
	bool collidingY = (p_mousePos.y > m_rect.top && p_mousePos.y < m_rect.top + m_rect.height);

	if (collidingX && collidingY)
		ClickedFunc();

	m_text.setPosition(m_rect.left + m_rect.width / 6, m_rect.top + m_rect.height / 4);
}

void PauseSoundButton::ClickedFunc()
{
	m_isSoundEnabled = !m_isSoundEnabled;
	SoundManager::Instance().StopSound(m_isSoundEnabled);
}

void PauseSoundButton::Draw(sf::RenderWindow &p_window)
{
	if (m_isSoundEnabled)
		m_text.setString("Background Music is Disabled!");
	else
		m_text.setString("Background Music is Enabled!");

	p_window.draw(m_background);
	p_window.draw(m_text);
}

