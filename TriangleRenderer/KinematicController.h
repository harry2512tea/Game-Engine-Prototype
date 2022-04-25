#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Kinematic.h"
#include "Object.h"

class KinematicController
{
	KinematicController();
	static KinematicController* getInstance();
	void CheckGeneralCollisions(std::vector<Object>& objs);
	void CheckPreciseCollision(Object& obj1, Object& obj2);

private:

	bool checkCollision(Object& obj1, Object& obj2);

	bool SpherePlaneCollision();
	bool SphereSphereCollision(Object& obj1, Object& obj2);
	static KinematicController* instance;
};