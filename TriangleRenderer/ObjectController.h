#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "DynamicObject.h"
#include "Object.h"

class ObjectController
{
public:
	
	static ObjectController* getInstance();

	void Update(std::vector<Object*>& objs, float deltaTime);

	void CheckGeneralCollisions(std::vector<Object*>& objs);
	void CheckCollisionResponse(Object* obj1, Object* obj2);

	glm::vec3 GetGravity() { return Gravity; };
	void SetGravity(glm::vec3 grav) { Gravity = grav; };

	float GetDensity() { return airDensity; };
	void SetDensity(float value) { airDensity = value; };
private:
	static ObjectController* instance;

	glm::vec3 Gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	float DeltaTime;
	float airDensity;

	bool checkCollision(Object* obj1, Object* obj2);

	bool SpherePlaneCollision(Object* Sphere, Object* Plane);
	bool SphereSphereCollision(Object* obj1, Object* obj2);

	
};