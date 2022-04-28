#pragma once
#include "Plane.h"

Plane::Plane(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 Position, glm::vec3 Scale)
{
	initialMax = A;
	initialMin = B;
	initialC = C;

	UpdatePoints(Position, Scale);
}

void Plane::UpdatePoints(glm::vec3 Position, glm::vec3 Scale)
{
	max = (initialMax * Scale) + Position;
	min = (initialMin * Scale) + Position;
	glm::vec3 CalcC = (initialC * Scale) + Position;
	//calculating the plane's normal
	normal = glm::cross((max - CalcC), (min - CalcC));
}

bool Plane::CheckIntersection(glm::vec3 Direction, glm::vec3 Origin, glm::vec3& Intersect)
{
	//Line Equation: (originX + directionX * T) + (originY + directionY * T) + (originX + directionY * T)
	//glm::vec3 PlaneCenter = max - glm::vec3(min.x / 2, min.y / 2, min.z / 2);
	float d = glm::dot(normal, (max - (min / 2.0f)));

	if (glm::dot(normal, Direction) == 0) return false;
	else
	{
		float x = (d - glm::dot(normal, Origin)) / glm::dot(normal, Direction);

		Intersect = Origin + (Direction * x);

		if ((Intersect.x >= min.x && Intersect.x <= max.x) &&
			(Intersect.y >= min.y && Intersect.y <= max.y) &&
			(Intersect.z >= min.z && Intersect.z <= max.z))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	

}