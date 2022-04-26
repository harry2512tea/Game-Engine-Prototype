#pragma once
#include "Kinematic.h"
#include "Object.h"
#include "KinematicController.h"

#include <math.h>


Kinematic::Kinematic(Object* obj) : attachedObj(obj)
{
	colliderType = 0;
	velocity = glm::vec3(0.0f);
	momentum = glm::vec3(0.0f);
	
}

void Kinematic::Update(float DeltaTime, std::vector<Object>& objs, int address)
{
	if (!isKinematic)
	{
		KinematicController* kin = KinematicController::getInstance();
		glm::vec3 currentPos = attachedObj->GetPosition();
		//std::cout << kin->GetGravity().y;
		glm::vec3 gravity = kin->GetGravity() * DeltaTime;
		AddVelocity(gravity);
		//std::cout << DeltaTime;
		//attachedObj->SetPosition(currentPos + (velocity /* * DeltaTime*/));
		attachedObj->translate(velocity);
		momentum = CalculateMomentum();
		/*for (int i = 0; i < objs.size(); i++)
		{
			if (i != address)
			{
				CheckCollision(objs[i]);
			}
		}*/

	}
}

bool Kinematic::CheckCollision(Object& obj)
{
	float x, y, z, dist;
	switch (colliderType)
	{
	case 0:
		switch (obj.GetColliderType())
		{
		case 0:
			return (attachedObj->min.x <= obj.max.x && attachedObj->max.x >= obj.max.x) &&
				(attachedObj->min.y <= obj.max.y && attachedObj->max.y >= obj.max.y) &&
				(attachedObj->min.z <= obj.max.z && attachedObj->max.z >= obj.max.z);
			break;

		case 1:
			glm::vec3 sphere = obj.GetPosition();
			x = fmaxf(attachedObj->min.x, fminf(sphere.x, attachedObj->max.x));
			y = fmaxf(attachedObj->min.y, fminf(sphere.y, attachedObj->max.y));
			z = fmaxf(attachedObj->min.z, fminf(sphere.z, attachedObj->max.z));

			dist = sqrt((x - sphere.x) * (x - sphere.x) +
				(y - sphere.y) * (y - sphere.y) +
				(z - sphere.z) * (x - sphere.z)
			);

			return dist < obj.GetSphereRadius();
			break;
		}
		break;

	case 1:
		switch (obj.GetColliderType())
		{
		case 0:
			glm::vec3 sphere = attachedObj->GetPosition();
			x = fmaxf(obj.min.x, fminf(sphere.x, obj.max.x));
			y = fmaxf(obj.min.y, fminf(sphere.y, obj.max.y));
			z = fmaxf(obj.min.z, fminf(sphere.z, obj.max.z));

			dist = sqrt((x - sphere.x) * (x - sphere.x) +
				(y - sphere.y) * (y - sphere.y) +
				(z - sphere.z) * (x - sphere.z)
			);

			return dist < attachedObj->GetSphereRadius();
			break;

		case 1:
			glm::vec3 a = attachedObj->GetPosition();
			glm::vec3 b = obj.GetPosition();

			dist = sqrt((a.x - b.x) * (a.x - b.x) +
				(a.y - b.y) * (a.y - b.y) +
				(a.z - b.z) * (a.z - b.z)
			);
			
			return dist < (attachedObj->GetSphereRadius() + obj.GetSphereRadius());
			break;

		}
		break;
	}
	return false;
}

int Kinematic::GetColliderType()
{
	// 0 = AABB
	// 1 = Sphere Collider
	return colliderType;
}

void Kinematic::SetColliderType(int col)
{
	colliderType = col;
}

glm::vec3 Kinematic::CalculateMomentum()
{
	return mass * velocity;
}

