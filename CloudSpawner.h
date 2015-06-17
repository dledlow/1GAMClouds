#pragma once
#include "Cloud.h"

class CloudSpawner
{
public:
	CloudSpawner(std::list<Entity*>* eList);
	~CloudSpawner();

	void Update();

	float spawnRate = 1;

	std::list<Entity*>* eList;
};

