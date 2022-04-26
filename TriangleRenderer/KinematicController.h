#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Kinematic.h"
#include "Object.h"

class KinematicController
{
public:
	static KinematicController* getInstance();
	void CheckGeneralCollisions(std::vector<Object>& objs);
	void CheckPreciseCollision(Object& obj1, Object& obj2);
	void DoWallCollision(glm::vec3 wallNormal, Kinematic* Rb);
	void DoMomentumCollision();

private:

	bool checkCollision(Object& obj1, Object& obj2);
	static KinematicController* instance;
};