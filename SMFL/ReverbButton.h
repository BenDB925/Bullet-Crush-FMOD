#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "Button.h"
#include "SFML\Graphics\CircleShape.hpp"

class ReverbButton : public Button
{
public:
	ReverbButton(sf::IntRect p_position);
	~ReverbButton();

	void Update(sf::Vector2i p_mousePos);
	void ClickedFunc();
	void Draw(sf::RenderWindow &p_window);

private:
	bool m_isReverbEnabled;
	sf::CircleShape m_circle;
};

