#include "Game.h"

/// <summary>
/// @author RP
/// @date June 2016
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
/// 
Game::Game()
: m_window(sf::VideoMode(1440, 900, 32), "SFML Playground", sf::Style::Default)
{	
	//Load Level
	int currentLevel = 1;
	if (!LevelLoader::load(currentLevel, m_Level))
	{
		return;
	}

	//Tank Sprite
	if (!m_Texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string s = "Error Loading From File";
		throw std::exception(s.c_str());
	}


	m_Tank.reset(new Tank(m_Texture, m_Level.m_tank.m_position));
	
	//Background Sprite
	if (!m_BackgroundTexture.loadFromFile(m_Level.m_background.m_fileName))
	{
		std::string s = "Error Loading From File";
		throw std::exception(s.c_str());
	}
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	sf::Sprite tempSprite;
	tempSprite.setTexture(m_Texture);
	for (auto &obstacle : m_Level.m_obstacles)
	{
		tempSprite.setPosition(obstacle.m_position);
		tempSprite.rotate(obstacle.m_rotation);
		m_sprites.push_back(tempSprite);
	}
}

/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}



/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
	m_Tank->update(MS_PER_UPDATE);
}

/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		case sf::Keyboard::Up:
			m_Tank->IncreaseSpeed();
			break;
		case sf::Keyboard::Down:
			m_Tank->DecreaseSpeed();
			break;
		case sf::Keyboard::Left:
			m_Tank->DecreaseRotation();
			break;
		case sf::Keyboard::Right:
			m_Tank->IncreaseRotation();
			break;
		case sf::Keyboard::A:
			m_Tank->DecreaseTurretAngle();
			break;
		case sf::Keyboard::D:
			m_Tank->IncreaseTurretAngle();
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_BackgroundSprite);
	m_window.draw(m_Sprite);
	m_Tank->render(m_window);
	for (auto &sprite : m_sprites)
	{
		m_window.draw(sprite);
	}
	m_window.display();
}

