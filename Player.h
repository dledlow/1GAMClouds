#pragma once
#include "Entity.h"

class Player :
	public Entity
{
public:
	Player();
	~Player();

	void Update(sf::Window* window, std::list<Entity*>* eList);
	void Render(sf::RenderWindow* window);
	void UpdateLaserCollisions(std::list<Entity*>* eList);

	bool laserActive;

	const float maxAngVelo = 2;			// degrees/frame
	const float acceleration =  0.1f;	// degrees/frame
	const float drag = 0.05f;			// degrees/frame

private:
	sf::Vector2i findIntersectingPoint(sf::Vector2i);

	sf::Vector2i laserEndPoint;
};

