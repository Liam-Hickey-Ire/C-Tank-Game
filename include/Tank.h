#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Math.hpp>

/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:	
	Tank(sf::Texture const & texture, sf::Vector2f const & pos);
	void update(double dt);
	void render(sf::RenderWindow & window);
	void IncreaseSpeed();
	void DecreaseSpeed();
	void IncreaseRotation();
	void DecreaseRotation();

	void IncreaseTurretAngle();
	void DecreaseTurretAngle();

	
private:
	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Texture const & m_texture;
	double m_speed = 0;
	double m_rotation = 0;

	double static const DEG_TO_RAD;

	int turretAddOn = 0;
		
};