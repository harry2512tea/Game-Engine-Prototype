#pragma once
#include "Kinematic.h"
#include "Object.h"
#include "KinematicController.h"

#include <math.h>


Kinematic::Kinematic(Object* obj) : attachedObj(obj)
{
	velocity = glm::vec3(5.0f, 0.0f, -0.0f);
}

void Kinematic::Update(float DeltaTime)
{
	if (!isKinematic)
	{
		KinematicController* kin = KinematicController::getInstance();
		//glm::vec3 currentPos = attachedObj->GetPosition();
		//std::cout << kin->GetGravity().y;
		glm::vec3 gravity = kin->GetGravity();
		//AddVelocity(gravity);
		//std::cout << DeltaTime << std::endl;
		AddForce(gravity * DeltaTime, VelocityChange);
		//std::cout << DeltaTime;
		//attachedObj->SetPosition(currentPos + (velocity /* * DeltaTime*/));
		std::cout << "Velocity: " << velocity.x << " " << velocity.y << " " << velocity.z << std::endl;
		std::cout << "DeltaTime: " << DeltaTime << std::endl;
		attachedObj->translation(glm::vec3(velocity.x, velocity.y, velocity.z) * DeltaTime);
		momentum = CalculateMomentum();
	}
}

void Kinematic::AddForce(glm::vec3 Force, ForceMode Mode)
{
	switch (Mode)
	{
	case VelocityChange:
		velocity += Force;
		break;

	case Impulse:
		velocity += (Force / mass);
		break;
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

