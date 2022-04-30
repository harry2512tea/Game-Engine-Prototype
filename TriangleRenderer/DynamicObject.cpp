#pragma once
#include "DynamicObject.h"
#include "Object.h"
#include "ObjectController.h"

#include <math.h>


DynamicObject::DynamicObject(Object* obj) : attachedObj(obj)
{
	//velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	//rotationalVel = glm::vec3(-0.0f, 0.0f, -0.0f);
}

void DynamicObject::Update(float DeltaTime)
{
	if (!isKinematic)
	{
		if (gravityAffected)
		{
			ObjectController* kin = ObjectController::getInstance();
			glm::vec3 gravity = kin->GetGravity();
			AddForce(gravity * DeltaTime, VelocityChange);
		}
		
		std::cout << "Velocity: " << velocity.x << " " << velocity.y << " " << velocity.z << std::endl;
		std::cout << "DeltaTime: " << DeltaTime << std::endl;

		Euler(DeltaTime);

		attachedObj->rotate(glm::degrees(rotationalVel) * DeltaTime);
		std::cout << rotationalVel.x << " " << rotationalVel.y << " " << rotationalVel.z << std::endl;
		momentum = CalculateMomentum();
	}
}

void DynamicObject::AddForce(glm::vec3 Force, ForceMode Mode)
{
	switch (Mode)
	{
	case VelocityChange:
		velocity += Force;
		break;

	case Impulse:
		force += Force;
		break;
	}
}

int DynamicObject::GetColliderType()
{
	// 0 = AABB
	// 1 = Sphere Collider
	return colliderType;
}

void DynamicObject::SetColliderType(int col)
{
	colliderType = col;
}

glm::vec3 DynamicObject::CalculateMomentum()
{
	return mass * velocity;
}

void DynamicObject::Euler(float DeltaTime)
{
	float oneOverMass = 1 / mass;
	velocity += (force * oneOverMass * DeltaTime);
	attachedObj->translation(velocity * DeltaTime);
}