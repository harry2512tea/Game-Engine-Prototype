#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Kinematic.h"
#include "Object.h"

class KinematicController
{
public:
	void Update(std::vector<Object*>& objs);
	static KinematicController* getInstance();
	void CheckGeneralCollisions(std::vector<Object*>& objs);
	void CheckPreciseCollision(Object* obj1, Object* obj2);
	glm::vec3 GetGravity() { return Gravity; };
	glm::vec3 SetGravity(glm::vec3 grav) { Gravity = grav; };

private:
	glm::vec3 Gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	bool checkCollision(Object* obj1, Object* obj2);

	bool SpherePlaneCollision(Object* Sphere, Object* Plane);
	bool SphereSphereCollision(Object* obj1, Object* obj2);
	glm::vec3 nearestPoint(glm::vec3 posOnPlane, Object* AABB);
	static KinematicController* instance;
};