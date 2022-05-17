#include "Time.h"

SceneTime* SceneTime::instance = nullptr;

SceneTime* SceneTime::getInstance()
{
	if (!instance)
	{
		instance = new SceneTime();
	}

	return instance;
}