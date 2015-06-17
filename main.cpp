#include "Player.h"
#include "CloudSpawner.h"


std::list<Entity*> eList;
CloudSpawner csp(&eList);
sf::Texture* planetTex;

void doStuff(sf::RenderWindow* window){
	csp.Update();
	std::list<Entity*>::iterator it = eList.begin();
	while(it != eList.end()) {
		(*it)->Update(window, &eList);
		if ((*it)->pendingDelete){
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
	planet.setPosition(CENTRE.x - PLANETSIZE, CENTRE.y - PLANETSIZE);
	window->draw(planet);

	window->display();
}


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "SFML works!", sf::Style::Default, settings);
	window.setFramerateLimit(120);

	eList.push_front(new Player());

	planetTex = new sf::Texture();
	planetTex->loadFromFile("Assets/Planet1.png");

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