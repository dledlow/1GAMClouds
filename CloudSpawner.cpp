#include "CloudSpawner.h"


CloudSpawner::CloudSpawner(std::list<Entity*>* eList)
{
	this->eList = eList;
}


CloudSpawner::~CloudSpawner()
{
}


void CloudSpawner::Update()
{
	if (std::rand() < spawnRate*RAND_MAX)
	{
		eList->push_front(new Cloud(randf() * 360, randf(), randf() + 0.5f));
	}
}