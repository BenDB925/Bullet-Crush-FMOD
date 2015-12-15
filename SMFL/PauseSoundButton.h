#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "Button.h"

class PauseSoundButton : public Button
{
public:
	PauseSoundButton(sf::IntRect p_position);
	~PauseSoundButton();

	void Update(sf::Vector2i p_mousePos);
	void ClickedFunc();
	void Draw(sf::RenderWindow &p_window);

private:
	bool m_isSoundEnabled;
};

