#pragma once
#include "Entity.h"

class ScoreCounter : 
	public Entity
{
public:
	ScoreCounter(float x,float y);
	~ScoreCounter();

	sf::Text scoreText;
	sf::Text highScoreText;
	sf::Text multiplierText;
	sf::Font font;

	int score = 0;
	int highScore = 0;
	float multiplier = 1.0f;

	void Update();
	void Render(sf::RenderWindow* window);

	void addScore(int score);
	void addMultiplier(float mult);

	void reset();
};

