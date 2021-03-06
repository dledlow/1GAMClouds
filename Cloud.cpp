#include "Cloud.h"


static sf::Texture* tex;

Cloud::Cloud() : Entity(0, 0)
{
	if (tex == NULL) {
		tex = new sf::Texture();
		tex->loadFromFile("Assets/Cloud.png");
	}

	type = new sf::String("cloud");
	r = 1000;

	shape = sf::CircleShape(radius, 5);
	//shape.setFillColor(sf::Color::Magenta);
	shape.setTexture(tex);
	shape.setOrigin(radius, radius);
}


Cloud::Cloud(float theta, float dtheta, float fallSpeed) : Cloud()
{
	this->theta = theta;
	this->dtheta = dtheta;
	this->fallSpeed = fallSpeed;
	CollisionType = CollisionTypes::KILLABLE;
}


Cloud::~Cloud()
{
}


void Cloud::Update(sf::Window* window, std::list<Entity*>* eList)
{
	r -= fallSpeed;
	if (r < PLANETSIZE){
		pendingDelete = true;
		type = new sf::String("didDamage");
	}

	theta += dtheta;
	dtheta = abs(dtheta) < drag ? 0 : dtheta - sgn(dtheta)*drag;

	x = cosf(theta * PI / 180) * r + CENTRE.x;
	y = sinf(theta * PI / 180) * r + CENTRE.y;
}


void Cloud::Render(sf::RenderWindow* window)
{
	shape.setPosition(x, y);
	shape.setRotation(theta-90);
	window->draw(shape);
}
