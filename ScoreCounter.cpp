#include "ScoreCounter.h"


ScoreCounter::ScoreCounter(float x, float y) : Entity(x,y)
{
	if (!font.loadFromFile("Assets/courier-new.ttf"))
	{
		// error...
	}

	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setColor(sf::Color::Red);
	scoreText.setPosition(x, y + 26);
	scoreText.setString("0");

	highScoreText.setFont(font);
	highScoreText.setCharacterSize(24);
	highScoreText.setColor(sf::Color::Red);
	highScoreText.setPosition(x, y);
	highScoreText.setString("0");

	multiplierText.setFont(font);
	multiplierText.setCharacterSize(24);
	multiplierText.setColor(sf::Color::Red);
	multiplierText.setPosition(x, y + 52);
	multiplierText.setString(std::to_string(multiplier));
}


ScoreCounter::~ScoreCounter()
{
}


void ScoreCounter::Update(){
	scoreText.setString(std::to_string(score));
	highScoreText.setString(std::to_string(highScore));
	multiplierText.setString("x" + std::to_string(multiplier));
}


void ScoreCounter::Render(sf::RenderWindow* window)
{
	window->draw(highScoreText);
	window->draw(scoreText);
	window->draw(multiplierText);
}


void ScoreCounter::addScore(int score){
	this->score += std::round(score*multiplier);
	highScore = std::max(this->score, highScore);
}


void ScoreCounter::addMultiplier(float mult){
	this->multiplier += mult;
}


void ScoreCounter::reset(){
	score = 0;
	multiplier = 1;
}