#pragma once
#include "DynamicObject.h"
#include "Object.h"
#include "ObjectController.h"

#include <math.h>


DynamicObject::DynamicObject(Object* obj) : attachedObj(obj)
{
	//velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	//rotationalVel = glm::vec3(-0.0f, 0.0f, -0.0f);

	switch (attachedObj->GetColliderType())
	{
	case 0:
		float width, height, depth;
		width = attachedObj->size.x;
		height = attachedObj->size.y;
		depth = attachedObj->size.z;
		float Ih, Iw, Id;
		Ih = (1 / 12) * mass * (width * width + depth * depth);
		Iw = (1 / 12) * mass * (depth * depth + height * height);
		Id = (1 / 12) * mass * (width * width + height * height);

		InertiaTensorBody = glm::mat3(
			Iw, 0, 0,
			0, Ih, 0,
			0, 0, Id);
		break;
	case 1:
		momentOfInertia = (2 / 5) * mass * attachedObj->GetSphereRadius() * attachedObj->GetSphereRadius();
		InertiaTensorBody = glm::mat3(momentOfInertia);
		break;
	}
}

void DynamicObject::Update(float DeltaTime)
{
	//checking if the object is dynamic or kinematic
	if (!isKinematic)
	{
		//adding the gravitational force to the object
		if (gravityAffected)
		{
			ObjectController* kin = ObjectController::getInstance();
			glm::vec3 gravity = kin->GetGravity();
			AddForce(gravity * DeltaTime, VelocityChange);
		}
		
		//std::cout << "Velocity: " << velocity.x << " " << velocity.y << " " << velocity.z << std::endl;
		//std::cout << "DeltaTime: " << DeltaTime << std::endl;

		Drag(DeltaTime);

		//checking which update type to use
		switch (UpdateType)
		{
		case 0:
			Euler(DeltaTime);
			break;
		case 1:
			RungeKutta2(DeltaTime);
			break;
		case 2:
			RungeKutta4(DeltaTime);
			break;
		case 3:
			Vertlet(DeltaTime);
			break;
		}

		angular_momentum = ((2 / 5) * mass * attachedObj->GetSphereRadius() * attachedObj->GetSphereRadius()) * rotationalVel;
		CalculateAngularVelocity();
		//updating the object's rotation by the rotational momentum
		attachedObj->rotate(-glm::degrees(angular_velocity) * DeltaTime);
		//std::cout << velocity.x << " " << velocity.y << " " << velocity.z << std::endl;

		//updating the objects momentum
		momentum = CalculateMomentum();

		//resetting the forces acting on the object
		force = glm::vec3(0.0f);
	}
}
glm::vec3 DynamicObject::CalculateAngularVelocity()
{
	angular_velocity = mass * attachedObj->GetSphereRadius() * attachedObj->GetSphereRadius() * angular_momentum;
	return angular_velocity;
}
void DynamicObject::AddTorque(glm::vec3 torque)
{
	glm::vec3 changeInAngMomentum = torque - angular_momentum;
	angular_momentum += changeInAngMomentum;
}

void DynamicObject::AddForce(glm::vec3 Force, ForceMode Mode)
{
	switch (Mode)
	{
	//An instant change to the velocity, ignoring the object's mass
	case VelocityChange:
		velocity += Force;
		break;

	//an instant force on the object, using its mass
	case Impulse:
		force += Force;
		break;
	}
}

void DynamicObject::Drag(float deltaTime)
{
	float pi = 3.1416f;

	float radius = attachedObj->GetSphereRadius()/10;

	//density of dry air, at sea level, at 15 degrees C.
	float airDensity = ObjectController::getInstance()->GetDensity();

	// equation found here: https://www.engineersedge.com/fluid_flow/sphere_surface_drag_14044.htm
	float frontalArea = (pi * radius * radius) / 4;

	//typical drag coefficient table: https://courses.lumenlearning.com/physics/chapter/5-2-drag-forces/
	float C = 0.45f;

	//drag equation: https://www.grc.nasa.gov/www/k-12/airplane/drageq.html#:~:text=The%20drag%20equation%20states%20that,times%20the%20reference%20area%20A.&text=For%20given%20air%20conditions%2C%20shape,for%20Cd%20to%20determine%20drag.
	glm::vec3 drag = C * ((airDensity * velocity * velocity) / 2.0f) * frontalArea;
	 
	drag *= -glm::normalize(velocity);

	//adding the drag force to the object
	AddForce(drag, Impulse);
}

void DynamicObject::Euler(float DeltaTime)
{
	float oneOverMass = 1 / mass;
	velocity += (force * oneOverMass * DeltaTime);
	attachedObj->translation(velocity * DeltaTime);
}

void DynamicObject::RungeKutta2(float deltaTime)
{
	glm::vec3 _force;
	glm::vec3 acceleration;
	glm::vec3 k0, k1;
	_force = force;
	acceleration = _force / mass;
	k0 = acceleration * deltaTime;

	_force = force + k0 / 2.0f;
	acceleration = _force / mass;
	k1 = acceleration * deltaTime;

	velocity += k1;
	attachedObj->translation(velocity * deltaTime);
}

void DynamicObject::RungeKutta4(float deltaTime)
{
	glm::vec3 _force;
	glm::vec3 acceleration;
	glm::vec3 k0, k1, k2, k3;

	_force = force;
	acceleration = _force / mass;
	k0 = acceleration * deltaTime;

	_force = force + k0 / 2.0f;
	acceleration = _force / mass;
	k1 = acceleration * deltaTime;

	_force = force + k1 / 2.0f;
	acceleration = _force / mass;
	k2 = acceleration * deltaTime;

	_force = force + k2;
	acceleration = _force / mass;
	k3 = acceleration * deltaTime;

	velocity += (k0 + 2.0f * k1 + 2.0f * k2 + k3) / 6.0f;
	attachedObj->translation(velocity * deltaTime);
}

void DynamicObject::Vertlet(float deltaTime)
{
	glm::vec3 _force;
	glm::vec3 acceleration;
	glm::vec3 previousPosition;

	_force = force;
	acceleration = _force / mass;

	previousPosition = attachedObj->GetPosition() - velocity * deltaTime + 0.5f * acceleration * (deltaTime * deltaTime);
	attachedObj->SetPosition(-previousPosition + 2.0f * attachedObj->GetPosition() + acceleration * deltaTime * deltaTime);

	velocity = attachedObj->GetPosition() - previousPosition / (2.0f * deltaTime);
	velocity += acceleration * deltaTime;
}

void DynamicObject::SetRotationalVel(glm::vec3 rot)
{
	rotationalVel = rot; 
	angular_momentum = rot / (mass * attachedObj->GetSphereRadius() * attachedObj->GetSphereRadius());
}