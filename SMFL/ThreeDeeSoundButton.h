#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "Button.h"

class ThreeDeeSoundButton : public Button
{
public:
	ThreeDeeSoundButton(sf::IntRect p_position);
	~ThreeDeeSoundButton();

	void Update(sf::Vector2i p_mousePos);
	void ClickedFunc();
	void Draw(sf::RenderWindow &p_window);
	bool Is3DEnabled();

private:
	bool m_is3DEnabled;
};

