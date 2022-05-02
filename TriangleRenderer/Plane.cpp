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
	//setting the new max point
	max = (initialMax * Scale) + Position;

	//setting the new min point
	min = (initialMin * Scale) + Position;

	//calculating the third point
	C = (initialC * Scale) + Position;

	//calculating the plane's normal
	normal = glm::normalize(glm::cross((max - C), (min - C)));

	//used for testing
	//normal = glm::vec3(round(normal.x), round(normal.y), round(normal.z));
}

bool Plane::CheckIntersection(glm::vec3 Direction, glm::vec3 Origin, glm::vec3& Intersect)
{
	//returns 0 if the direction is perpendicular to the plane
	float d = glm::dot(normal, max);

	
	if (glm::dot(normal, Direction) == 0)
	{
		//direction does not intersect the plane
		std::cout << "check intersection returning false 1" << std::endl;
		return false;
	}
	else
	{

		float x = (d - glm::dot(normal, Origin)) / glm::dot(normal, Direction);

		//calculates the point of intersection
		Intersect = Origin + (Direction * x);

		//checks if that intersection is within the plane's boundaries
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
	//returns 0 if the direction is perpendicular to the plane
	float d = glm::dot(normal, max);

	if (glm::dot(normal, Direction) == 0)
	{
		//direction does not intersect the plane
		return false;
	}
	else
	{
		//calculates the point of intersection
		float x = (d - glm::dot(normal, Origin)) / glm::dot(normal, Direction);
		Intersect = Origin + (Direction * x);
		return true;
	}
}


