#pragma once
#include "Entity.h"


class Cloud :
	public Entity
{
public:
	Cloud();
	Cloud(float theta, float dtheta, float fallSpeed);
	~Cloud();

	void Update(sf::Window* window, std::list<Entity*>* eList);
	void Render(sf::RenderWindow* window);

	float fallSpeed = 1;
	sf::CircleShape shape;
};

