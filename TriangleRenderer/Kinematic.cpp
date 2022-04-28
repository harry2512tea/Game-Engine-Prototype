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

void Kinematic::Update(float DeltaTime)
{
	if (!isKinematic)
	{
		KinematicController* kin = KinematicController::getInstance();
		//glm::vec3 currentPos = attachedObj->GetPosition();
		//std::cout << kin->GetGravity().y;
		glm::vec3 gravity = kin->GetGravity() * DeltaTime;
		AddVelocity(gravity);
		//std::cout << DeltaTime;
		//attachedObj->SetPosition(currentPos + (velocity /* * DeltaTime*/));
		std::cout << "Velocity: " << velocity.x << " " << velocity.y << " " << velocity.z << std::endl;
		attachedObj->translation(glm::vec3(velocity.x, velocity.y, velocity.z) * DeltaTime);
		momentum = CalculateMomentum();
	}
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

