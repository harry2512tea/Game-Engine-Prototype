#pragma once
#include "Component.h"
#include <glm/glm.hpp>
//class Object;

class Collider : public Component
{
public:
	Collider(Object* obj);
protected:
	/*
	Key:
	0 : AABB
	1 : OBB
	2 : Sphere
	*/
	int ColliderType = 0;

	glm::vec3 min, max, initialMin, initialMax, previousPos, previousRot, previousScale;

	void UpdateAABB();
};