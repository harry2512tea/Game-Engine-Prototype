#pragma once
#include "Kinematic.h"
#include "Object.h"

#include <math.h>

Kinematic::Kinematic(Object* obj) : attachedObj(obj)
{
	colliderType = 0;
	velocity = glm::vec3(0.0f);
}

void Kinematic::Update(float DeltaTime, std::vector<Object>& objs, int address)
{
	if (isKinematic)
	{
		glm::vec3 currentPos = attachedObj->GetPosition();
		attachedObj->SetPosition(glm::vec3(
			currentPos.x + (velocity.x * DeltaTime),
			currentPos.y + (velocity.y * DeltaTime),
			currentPos.z + (velocity.z * DeltaTime)
		));
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

void Kinematic::setKinematic(bool value)
{
	isKinematic = value;
}

bool Kinematic::CheckCollision(Object& obj)
{
	
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
			float x = fmaxf(attachedObj->min.x, fminf(sphere.x, attachedObj->max.x));
			float y = fmaxf(attachedObj->min.y, fminf(sphere.y, attachedObj->max.y));
			float z = fmaxf(attachedObj->min.z, fminf(sphere.z, attachedObj->max.z));

			float dist = sqrt((x - sphere.x) * (x - sphere.x) +
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
			float x = fmaxf(obj.min.x, fminf(sphere.x, obj.max.x));
			float y = fmaxf(obj.min.y, fminf(sphere.y, obj.max.y));
			float z = fmaxf(obj.min.z, fminf(sphere.z, obj.max.z));

			float dist = sqrt((x - sphere.x) * (x - sphere.x) +
				(y - sphere.y) * (y - sphere.y) +
				(z - sphere.z) * (x - sphere.z)
			);

			return dist < attachedObj->GetSphereRadius();
			break;

		case 1:
			glm::vec3 a = attachedObj->GetPosition();
			glm::vec3 b = obj.GetPosition();

			float dist = sqrt((a.x - b.x) * (a.x - b.x) +
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

float Kinematic::CalculateMomentum()
{
	return mass * glm::length(velocity);
}

float Kinematic::GetMass()
{
	return mass;
}
