#include "Player.h"

static sf::Texture* tex;

Player::Player() : Entity(0,0)
{
	if (tex == NULL) {
		tex = new sf::Texture();
		tex->loadFromFile("Assets/Player.png");
	}

	laserActive = false;
	isDead = false;
	radius = 10;
	r = PLANETSIZE + radius;
	scoreBoard = new ScoreCounter(10, 10);
	clock.restart();

	shape = sf::CircleShape(radius+10, 10);
	shape.setTexture(tex);
	shape.setOrigin(radius+5, radius+5);
}


Player::~Player()
{
}


void Player::Update(sf::Window* window, std::list<Entity*>* eList)
{
	killsSinceLastTick = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dtheta = std::min(dtheta + acceleration, maxAngVelo);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dtheta = std::max(dtheta - acceleration, -maxAngVelo);
	}

	theta += dtheta;
	dtheta = abs(dtheta) < drag ? 0 : dtheta - sgn(dtheta)*drag;

	x = cosf(theta * PI / 180) * r + CENTRE.x;
	y = sinf(theta * PI / 180) * r + CENTRE.y;

	laserActive = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2i intPoint = findIntersectingPoint(mousePos);
		if (intPoint.x == -1 && intPoint.y == -1)
		{
			laserEndPoint = mousePos;
			laserEndPoint.x = 1000.0f * (laserEndPoint.x - x) + x;
			laserEndPoint.y = 1000.0f * (laserEndPoint.y - y) + y;
			DetectLaserCollisions(eList);	// only collide if we havent blocked the shot with the planet
		}
		else{
			laserEndPoint = intPoint;
		}

		laserActive = true;
	}
	DetectFatalCollisions(eList);
	scoreBoard->addMultiplier(clock.restart().asSeconds());
	scoreBoard->addScore(killsSinceLastTick);
	scoreBoard->Update();

}


void Player::Render(sf::RenderWindow* window)
{
	shape.setRotation(theta);
	shape.setPosition(x, y);
	window->draw(shape);

	if (laserActive){
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x, y),sf::Color::Red),
			sf::Vertex(sf::Vector2f(float(laserEndPoint.x), float(laserEndPoint.y)), sf::Color::Blue)
		};
		
		window->draw(line, 2, sf::Lines);
	}
	scoreBoard->Render(window);
}


sf::Vector2i Player::findIntersectingPoint(sf::Vector2i mousePos){
	return collideCircleWithLine(CENTRE, PLANETSIZE, mousePos, sf::Vector2i(x, y));
}


void Player::DetectLaserCollisions(std::list<Entity*>* eList){
	std::list<Entity*>::iterator it = eList->begin();
	while (it != eList->end()) {
		if ((*it)->CollisionType & CollisionTypes::KILLABLE){
			sf::Vector2i* hitPoint = &collideCircleWithLine(sf::Vector2i((*it)->x, (*it)->y), (*it)->radius, laserEndPoint, sf::Vector2i(x, y));
			if (hitPoint->x != -1 || hitPoint->y != -1){
				(*it)->pendingDelete = true;
				killsSinceLastTick++;
			}
		}
		++it;
	}
}


void Player::DetectFatalCollisions(std::list<Entity*>* eList){
	std::list<Entity*>::iterator it = eList->begin();
	while (it != eList->end()) {
		if ((*it)->CollisionType & CollisionTypes::DANGEROUS){
			if (distance((*it)->x, (*it)->y, x, y) <= (*it)->radius + radius){
				isDead = true;
			}
		}
		++it;
	}
}

void Player::reset() {
	clock.restart();
	theta = 0;
	dtheta = 0;
	scoreBoard->reset();
	isDead = false;
}