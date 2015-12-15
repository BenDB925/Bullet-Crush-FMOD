#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\Text.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"

class Button
{
public:
	Button();
	Button(sf::IntRect p_position);
	~Button();

	virtual void Update(sf::Vector2i p_mousePos) = 0;
	virtual void ClickedFunc() = 0;
	virtual void Draw(sf::RenderWindow &p_window) = 0;

protected:
	sf::IntRect m_rect;
	sf::Font m_font;
	sf::Text m_text;
	sf::RectangleShape m_background;
};

