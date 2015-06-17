#pragma once
#include "GlobalVariables.h"
#include "UtilityFunctions.h"

enum CollisionTypes {
	NOCOLLIDE = 0,
	KILLABLE = 1
};

class Entity
{
public:
	Entity(float x, float y);
	~Entity();

	virtual void Update(sf::Window* window, std::list<Entity*>* eList) {}
	virtual void Render(sf::RenderWindow* window) {}

	float x;
	float y;
	float theta;	// degrees
	float dtheta;	// degrees
	float r;
	float radius = 30;
	const float drag = 0;
	int CollisionType = 0;

	sf::Vector2f v;
	sf::Vector2f a;

	bool pendingDelete = false;
};