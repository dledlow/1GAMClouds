#include "Entity.h"

Entity::Entity(float x, float y)
{
	this->x = x;
	this->y = y;
	v = sf::Vector2f(0, 0);
	a = sf::Vector2f(0, 0);
	theta = 0;
	dtheta = 0;
	r = 0;
}


Entity::~Entity()
{

}


/*
void Entity::Update()
{
	v.x += a.x;
	v.y += a.y;

	x += v.x;
	y += v.y;
}

void Entity::Render(sf::RenderWindow* window)
{
	sf::CircleShape triangle(10, 3);
	triangle.setPosition(x-10, y-10);
	window->draw(triangle);
}
*/