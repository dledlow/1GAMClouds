#pragma once
#include "ScoreCounter.h"

class Player :
	public Entity
{
public:
	Player();
	~Player();

	void Update(sf::Window* window, std::list<Entity*>* eList);
	void Render(sf::RenderWindow* window);

	void DetectLaserCollisions(std::list<Entity*>* eList);
	void DetectFatalCollisions(std::list<Entity*>* eList);

	bool laserActive;
	bool isDead;

	int killsSinceLastTick;

	const float maxAngVelo = 2;			// degrees/frame
	const float acceleration =  0.1f;	// degrees/frame
	const float drag = 0.05f;			// degrees/frame

	ScoreCounter* scoreBoard;
	sf::Clock clock;

private:
	sf::Vector2i findIntersectingPoint(sf::Vector2i);

	sf::Vector2i laserEndPoint;
};

