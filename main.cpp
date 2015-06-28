#include "Player.h"
#include "CloudSpawner.h"


std::list<Entity*> eList;
CloudSpawner csp(&eList);
sf::Texture* planetTex;
Player* player;
sf::Text* deathText;
sf::Text* deathText2;
int planetHealth = 5;
int difficulty = 0;

void doStuff(sf::RenderWindow* window){
	if (player->isDead){
		if (deathText->getColor() == sf::Color::Transparent)
			deathText->setColor(sf::Color::Red);
		if (deathText2->getColor() == sf::Color::Transparent)
			deathText2->setColor(sf::Color::Red);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			deathText->setColor(sf::Color::Transparent);
			deathText2->setColor(sf::Color::Transparent);
			planetHealth = 5;
			player->reset();
			csp.reset();
			
			std::list<Entity*>::iterator it = eList.begin();
			while (it != eList.end()) {
				eList.erase(it++);
			}
			eList.push_front(player);
		}
		return;
	}

	difficulty = int(std::floor(player->scoreBoard->multiplier / 10));
	csp.dangerSpawnRate = difficulty*0.01;

	csp.Update();
	std::list<Entity*>::iterator it = eList.begin();
	while(it != eList.end()) {
		(*it)->Update(window, &eList);
		if ((*it)->pendingDelete){
			if ((*it)->type->find(sf::String("didDamage")) != sf::String::InvalidPos){
				planetHealth--;
			}
			if (planetHealth <= 0)
				player->isDead = true;

			eList.erase(it++);
		}
		else {
			++it;
		}
	}
}


void renderThings(sf::RenderWindow* window){

	window->clear();

	for (std::list<Entity*>::iterator it = eList.begin(); it != eList.end(); it++) {
		(*it)->Render(window);
	}

	sf::CircleShape planet(PLANETSIZE);
	//planet.setFillColor(sf::Color::Green);
	planet.setTexture(planetTex);
	planet.setFillColor(sf::Color(255, planetHealth * 51, planetHealth * 51));
	planet.setPosition(CENTRE.x - PLANETSIZE, CENTRE.y - PLANETSIZE);
	window->draw(planet);
	window->draw(*deathText);
	window->draw(*deathText2);

	window->display();
}


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Clouds", sf::Style::Default, settings);
	window.setFramerateLimit(144);

	player = new Player();
	eList.push_front(player);

	planetTex = new sf::Texture();
	planetTex->loadFromFile("Assets/Planet1.png");

	sf::Font font;
	font.loadFromFile("Assets/courier-new.ttf");
	deathText = new sf::Text();
	deathText->setFont(font);
	deathText->setCharacterSize(200);
	deathText->setColor(sf::Color::Transparent);
	deathText->setPosition(200, 200);
	deathText->setString("You Died");

	deathText2 = new sf::Text();
	deathText2->setFont(font);
	deathText2->setCharacterSize(50);
	deathText2->setColor(sf::Color::Transparent);
	deathText2->setPosition(400, 420);
	deathText2->setString("Press R to Restart");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		doStuff(&window);
		renderThings(&window);

	}

	return 0;
}