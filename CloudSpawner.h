#pragma once
#include "Cloud.h"
#include "DangerCloud.h"

class CloudSpawner
{
public:
	CloudSpawner(std::list<Entity*>* eList);
	~CloudSpawner();

	void Update();
	void reset();

	float spawnRate = 1;
	float dangerSpawnRate = 0.01;

	std::list<Entity*>* eList;
};

