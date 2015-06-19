#pragma once
#include "Entity.h"

class DangerCloud :
	public Entity
{
public:
	DangerCloud();
	DangerCloud(float theta, float dtheta, float fallSpeed);
	~DangerCloud();

	void Update(sf::Window* window, std::list<Entity*>* eList);
	void Render(sf::RenderWindow* window);

	float fallSpeed = 1;
	sf::CircleShape shape;
};

