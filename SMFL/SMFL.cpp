//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES

#include "Player.h"
#include "BulletManager.h"
#include "PlControls.h"
#include "EnemyManager.h"
#include "Level.h"
#include "CollisionManager.h"
#include "UI.h"
#include "SoundManager.h"
#include "Score.h"
#include "ReverbButton.h"
#include "ThreeDeeSoundButton.h"
#include "DopplerButton.h"
#include "PauseSoundButton.h"


// Game Modes
//////////////////
const byte MAINMENU = 0, GAME = 1, GAMEOVER = 2;
byte gameMode = MAINMENU;

// Variables
//////////////////
sf::Clock myClock;
sf::Time deltaTime;
Player player;
Level level;
sf::Texture m_tex, m_bgTex, m_titleTex;
sf::Sprite m_titleSpr;
std::vector<sf::Texture> m_backGroundTex;
sf::Vector2f screenDimensions = sf::Vector2f(600, 800);
int fps = 0;
sf::Font font;
sf::Text text;
sf::Text cScoreTxt, hScoreTxt, livesTxt;
ReverbButton reverbButton = ReverbButton(sf::IntRect(5, 690, 200, 20));
ThreeDeeSoundButton threeDeeButton = ThreeDeeSoundButton(sf::IntRect(5, 750, 200, 20));
DopplerButton dopplerButton = DopplerButton(sf::IntRect(5, 720, 200, 20));
PauseSoundButton pauseSoundButton = PauseSoundButton(sf::IntRect(5, 780, 200, 20));

//////////////////
const byte m_MAXLEVELS = 1;
//////////////////
void Init()
{
	player = Player(*&m_tex, sf::Vector2f(280, 600));
	level = Level(*&m_backGroundTex, screenDimensions);
	UI::Instance().Init(*&m_tex);
	SoundManager::Instance().Init();
	Score::Instance().Init();
	BulletManager::Instance().Init(*&m_tex);
	EnemyManager::Instance().Init(*&m_tex);
	CollisionManager::Instance().Init();
}
void LoadContent()
{

	// Check that assets are been loaded
	m_tex.loadFromFile("../resources/sprite.png");
	m_titleTex.loadFromFile("../resources/title.png");
	m_titleSpr.setTexture(m_titleTex);
	m_titleSpr.setTextureRect(sf::IntRect(0, 0, 600, 800));

	for (int i = 0; i < m_MAXLEVELS; i++)
	{
		std::string text = "../resources/Level";
		text += std::to_string(i);
		text += ".png";
		m_bgTex.loadFromFile(text);
		m_backGroundTex.push_back(m_bgTex);
	}
}

// UPDATE GAME MODES
//////////////////
void(UpdateMainMenu())
{
	if (PlControls::Instance().GetAnyKey())
	{
		gameMode = GAME;
		SoundManager::Instance().PlaySoundBG(SoundManager::SoundsList::BACKGROUND_MUSIC_LEVEL_1);
	}
}
void(UpdateGame())
{
	level.Update(deltaTime.asSeconds());
	player.Update(deltaTime.asMicroseconds());
	BulletManager::Instance().Update(deltaTime, screenDimensions);
	EnemyManager::Instance().Update(player.getPosition(), deltaTime.asMicroseconds(), screenDimensions);
	CollisionManager::Instance().CheckCollisions(player.GetCollisionBox());
	CollisionManager::Instance().EnemBulletPl(&player);
	if (EnemyManager::Instance().ShouldCheckBoss())
		CollisionManager::Instance().CheckBossCollisions(player.GetCollisionBox());
	Score::Instance().UpdateScores();
	cScoreTxt.setString(Score::Instance().currentScoreText);
	hScoreTxt.setString(Score::Instance().highScoresText.at(0));
	livesTxt.setString("x" + std::to_string(player.GetLivesNum()));
}
void(UpdateGameOver())
{
}

// DRAW GAME MODES
//////////////////
void(DrawMainMenu(sf::RenderWindow &p_window))
{
	p_window.draw(m_titleSpr);
}
void(DrawGame(sf::RenderWindow &p_window))
{
		p_window.draw(level.getSprite());

		EnemyManager::Instance().Draw(p_window);
		BulletManager::Instance().Draw(p_window);

	int maxPlayerSprites = player.getSprite().size();

	if (!player.CheckIfHidden())
		for (int i = 0; i < maxPlayerSprites; i++)
			p_window.draw(player.getSprite().at(i));


	p_window.draw(UI::Instance().getSprite());
	pauseSoundButton.Draw(p_window);
	if (threeDeeButton.Is3DEnabled())
	{
		reverbButton.Draw(p_window);
		dopplerButton.Draw(p_window);
	}
	threeDeeButton.Draw(p_window);

	// Draw Score
	////////////////////
	p_window.draw(cScoreTxt);
	p_window.draw(hScoreTxt);
	p_window.draw(livesTxt);
}
void(DrawGameOver(sf::RenderWindow &p_window))
{
}


// UPDATE EVENT
/////////////////////////////
void Update()
{
	deltaTime = myClock.getElapsedTime();
	fps = 1.f / deltaTime.asSeconds();

	PlControls::Instance().Update(deltaTime);

	myClock.restart();



	// Update Game Modes
	/////////////////////////////
	switch (gameMode)
	{
	case MAINMENU:
		UpdateMainMenu();
		break;
	case GAME:
		UpdateGame();
		break;
	case GAMEOVER:
		UpdateGameOver();
		break;
	}
	SoundManager::Instance().UpdateSound(player.getPosition(), player.getVelocity());
}

// DRAW EVENT
/////////////////////////////
void Draw(sf::RenderWindow &p_window)
{
	// Clear Window
	p_window.clear();


	// Update Draw Modes
	/////////////////////////////
	switch (gameMode)
	{
	case MAINMENU:
		DrawMainMenu(p_window);
		break;
	case GAME:
		DrawGame(p_window);
		break;
	case GAMEOVER:
		DrawGameOver(p_window);
		break;
	}

	// Display Window
	p_window.display();
}

////////////////////////////////////////////////////////////
///Entry point of application 
//////////////////////////////////////////////////////////// 
int main()
{

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y, 32), "SFML First Program");

	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	//load a font
	font.loadFromFile("C:\\Windows\\Fonts\\consolaz.TTF");
	cScoreTxt.setFont(font);
	//text.setStyle(sf::Text::Bold);
	cScoreTxt.setCharacterSize(22);
	cScoreTxt.setPosition(40, 30);

	hScoreTxt.setFont(font);
	//text.setStyle(sf::Text::Bold);
	hScoreTxt.setCharacterSize(22);
	hScoreTxt.setPosition(244, 30);

	livesTxt.setFont(font);
	livesTxt.setCharacterSize(22);
	livesTxt.setPosition(60, 60);


	// Load Content
	/////////////////////////////
	LoadContent();

	// Initialize
	/////////////////////////////
	Init();

	

	// Game Loop
	/////////////////////////////
	while (window.isOpen())
	{
		// Keyboard Events
		/////////////////////////////
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePos = sf::Vector2i(Event.mouseButton.x, Event.mouseButton.y);
				pauseSoundButton.Update(mousePos);
				if (threeDeeButton.Is3DEnabled())
				{
					reverbButton.Update(mousePos);
					dopplerButton.Update(mousePos);
				}

				threeDeeButton.Update(mousePos);
			}				
		}

		// Update World, Events, Game
		/////////////////////////////
		Update();
		//FMODsys->update();

		// Draw World, Events, Game
		/////////////////////////////
		Draw(window);
	} 
	return EXIT_SUCCESS;
}



// Joystick Buttons
// (0, 0) - Y
// (0, 1) - A
// (0, 2) - X
// (0, 3) - B
// (0, 4) - Left Bumper
// (0, 5) - Right Bumper
// (0, 6) - Back Bumper
// (0, 7) - Start Bumper
// (0, 8) - Left Analog Press
// (0, 9) - Right Analog Press

// sf::Joystick::X - Left Analog X-Axis
// sf::Joystick::Y - Left Analog Y-Axis
// sf::Joystick::R - Right Analog X-Axis
// sf::Joystick::U - Right Analog Y-Axis
// sf::Joystick::PovX - D-Pad X-Axis
// sf::Joystick::PovY - D-Pad Y-Axis

//// JOYPAD CHECKS
////////////////////////////////////////////////////////////// 
//if (sf::Joystick::isConnected(0))
//{
//	std::cout << "Joypad 1 is connected" << std::endl;
//
//	// Check How Many Buttons Joypad 0 has
//	int buttonCount = sf::Joystick::getButtonCount(0);
//	std::cout << "Button count: " << buttonCount << std::endl;
//}
//else
//std::cout << "Joypad 1 is not connected" << std::endl;