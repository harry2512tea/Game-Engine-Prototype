#pragma once
#include <vector>
#include "glm/glm.hpp"
#include <iostream>

class Object;
class ObjectController;

enum ForceMode
{
	VelocityChange,
	Impulse
};

class DynamicObject
{
public:
	DynamicObject(Object* obj);
	void Update(float DeltaTime);
	
	//Get functions
	glm::vec3 GetMomentum() { return momentum; };
	glm::vec3 GetVelocity() { return velocity; };
	glm::vec3 GetRotVel() { return rotationalVel; };
	glm::vec3 GetAngularVelocity() { return angular_velocity; };
	glm::vec3 Gettorque() { return torque; };
	glm::vec3 GetAngular_momentum() { return angular_momentum; };
	glm::mat3 GetInertiaTensor() { return InertiaTensorBody; };
	float GetElasticity() { return elasticity; };
	float GetFriction() { return friction; };
	bool getKinematic() { return isKinematic; };
	float GetMass() { return mass; };

	//set functions
	void AddForce(glm::vec3 Force, ForceMode Mode);
	void AddVelocity(glm::vec3 vel) { velocity += vel; };
	void SetVelocity(glm::vec3 vel) { velocity = vel; };
	void SetRotationalVel(glm::vec3 rot);
	void setElasticity(float value) { elasticity = value; };
	void setFriction(float value) { friction = value; };
	void SetMass(float _mass) { mass = _mass; };
	void setKinematic(bool value) { isKinematic = value; };
	void AddTorque(glm::vec3 torque);
	void SetAngular_momentum() { };
	void SetAngular_velocity() { };

private:
	Object* attachedObj;

	glm::vec3 momentum;
	glm::vec3 velocity;
	glm::vec3 force;
	glm::vec3 rotationalVel;
	glm::mat3 InertiaTensorBody;
	float momentOfInertia;

	glm::vec3 torque;
	glm::vec3 angular_momentum;
	glm::vec3 angular_velocity;

	glm::vec3 CalculateMomentum() { return mass * velocity; };
	glm::vec3 CalculateAngularVelocity();
	
	void Drag(float deltaTime);

	int UpdateType = 1;
	void Euler(float deltaTime);
	void RungeKutta2(float deltaTime);
	void RungeKutta4(float deltaTime);
	void Vertlet(float deltaTime);

	bool isKinematic = true;
	bool gravityAffected = true;

	float elasticity, friction;
	float mass = 1.0f;
};