#pragma once
#include "Plane.h"
#include <iostream>
#include <glm/fwd.hpp>

Plane::Plane(glm::vec3 A, glm::vec3 C, glm::vec3 B, glm::vec3 Position, glm::vec3 Scale, glm::vec3 rotation)
{
	initialMax = A;
	initialMin = B;
	initialC = C;

	UpdatePoints(Position, Scale, rotation);
}

void Plane::UpdatePoints(glm::vec3 Position, glm::vec3 Scale, glm::vec3 rotation)
{
	/*Rotation = glm::quat(rotation);
	max = ((initialMax * Scale) * Rotation) + Position;
	min = ((initialMin * Scale) * Rotation) + Position;
	glm::vec3 CalcC = ((initialC * Rotation)* Scale) + Position;*/

	max = (initialMax * Scale) + Position;
	min = (initialMin * Scale) + Position;
	C = (initialC * Scale) + Position;
	//calculating the plane's normal
	normal = glm::normalize(glm::cross((max - C), (min - C)));
	normal = glm::vec3(round(normal.x), round(normal.y), round(normal.z));
}

bool Plane::CheckIntersection(glm::vec3 Direction, glm::vec3 Origin, glm::vec3& Intersect)
{
	//Line Equation: (originX + directionX * T) + (originY + directionY * T) + (originX + directionY * T)
	//glm::vec3 PlaneCenter = max - glm::vec3(min.x / 2, min.y / 2, min.z / 2);

	float d = glm::dot(normal, max);

	/*glm::vec3 diff = Origin - max;
	float prod1 = glm::dot(diff, normal);
	float prod2 = dot(Direction, normal);
	float prod3 = prod1 / prod2;*/

	if (glm::dot(normal, Direction) == 0)
	{
		std::cout << "check intersection returning false 1" << std::endl;
		return false;
	}
	else
	{
		float x = (d - glm::dot(normal, Origin)) / glm::dot(normal, Direction);

		//Intersect = Origin - Direction * prod3;

		//Intersect = Origin + (Direction * x);

		Intersect = Origin + (Direction * x);

		if ((Intersect.x >= min.x && Intersect.x <= max.x) &&
			(Intersect.y >= min.y && Intersect.y <= max.y) &&
			(Intersect.z >= min.z && Intersect.z <= max.z))
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

bool Plane::getIntersection(glm::vec3 Direction, glm::vec3 Origin, glm::vec3& Intersect)
{
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
		Intersect = Origin - Direction * prod3;
		std::cout << "Intersect Point: " << Intersect.x << " " << Intersect.y << " " << Intersect.z << std::endl;
		return true;
	}
}


