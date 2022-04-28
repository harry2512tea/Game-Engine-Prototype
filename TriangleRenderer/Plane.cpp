#pragma once
#include "Plane.h"
#include <iostream>

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
	normal = glm::normalize(glm::cross((max - CalcC), (min - CalcC)));
}

bool Plane::CheckIntersection(glm::vec3 Direction, glm::vec3 Origin, glm::vec3& Intersect)
{
	//Line Equation: (originX + directionX * T) + (originY + directionY * T) + (originX + directionY * T)
	//glm::vec3 PlaneCenter = max - glm::vec3(min.x / 2, min.y / 2, min.z / 2);

	//float d = glm::dot(normal, max);
	glm::vec3 diff = Origin - max;
	float prod1 = glm::dot(diff, normal);
	float prod2 = dot(Direction, normal);
	float prod3 = prod1 / prod2;

	if (glm::dot(normal, Direction) == 0)
	{
		return false;
	}
	else
	{
		//float x = (d - glm::dot(normal, Origin)) / glm::dot(normal, Direction);

		Intersect = Origin - Direction * prod3;

		//Intersect = Origin + (Direction * x);

		if ((Intersect.x <= min.x && Intersect.x >= max.x) &&
			(Intersect.y <= min.y && Intersect.y >= max.y) &&
			(Intersect.z <= min.z && Intersect.z >= max.z))
		{
			std::cout << "check intersection returning true" << std::endl;
			return true;
		}
		else
		{
			std::cout << "check intersection returning false" << std::endl;
			return false;
		}
	}
	

}