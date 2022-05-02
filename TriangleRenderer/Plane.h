#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Plane
{
public:
	Plane(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 Position, glm::vec3 Scale, glm::vec3 rotation);
	glm::vec3 max, initialMax;
	glm::vec3 min, initialMin;
	glm::vec3 C, initialC;
	glm::vec3 normal;
	
	void UpdatePoints(glm::vec3 Position, glm::vec3 Scale, glm::vec3 rotation);

	bool CheckIntersection(glm::vec3 Direction, glm::vec3 Origin, glm::vec3& Intersect);
	bool getIntersection(glm::vec3 Direction, glm::vec3 Origin, glm::vec3& Intersect);
};