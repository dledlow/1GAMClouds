#include "DangerCloud.h"


static sf::Texture* tex;

DangerCloud::DangerCloud() : Entity(0, 0)
{
	if (tex == NULL) {
		tex = new sf::Texture();
		tex->loadFromFile("Assets/Cloud.png");
	}

	r = 1000;

	shape = sf::CircleShape(radius, 10);
	shape.setFillColor(sf::Color::Magenta);
	shape.setTexture(tex);
	shape.setOrigin(radius, radius);
}


DangerCloud::DangerCloud(float theta, float dtheta, float fallSpeed) : DangerCloud()
{
	this->theta = theta;
	this->dtheta = dtheta;
	this->fallSpeed = fallSpeed;
	CollisionType = CollisionTypes::DANGEROUS;
}


DangerCloud::~DangerCloud()
{
}


void DangerCloud::Update(sf::Window* window, std::list<Entity*>* eList)
{
	r -= fallSpeed;
	if (r < PLANETSIZE){
		pendingDelete = true;
	}

	theta += dtheta;
	//dtheta = abs(dtheta) < drag ? 0 : dtheta - sgn(dtheta)*drag;

	x = cosf(theta * PI / 180) * r + CENTRE.x;
	y = sinf(theta * PI / 180) * r + CENTRE.y;
}


void DangerCloud::Render(sf::RenderWindow* window)
{
	shape.setPosition(x, y);
	shape.setRotation(theta - 90);
	window->draw(shape);
}
