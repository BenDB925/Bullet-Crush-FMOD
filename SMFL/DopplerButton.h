#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "Button.h"

class DopplerButton : public Button
{
public:
	DopplerButton(sf::IntRect p_position);
	~DopplerButton();

	void Update(sf::Vector2i p_mousePos);
	void ClickedFunc();
	void Draw(sf::RenderWindow &p_window);

private:
	bool m_isDopplerEnabled;
};

