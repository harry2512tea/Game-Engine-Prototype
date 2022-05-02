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
	float GetElasticity() { return elasticity; };
	float GetFriction() { return friction; };
	bool getKinematic() { return isKinematic; };
	float GetMass() { return mass; };

	//set functions
	void AddForce(glm::vec3 Force, ForceMode Mode);
	void AddVelocity(glm::vec3 vel) { velocity += vel; };
	void SetVelocity(glm::vec3 vel) { velocity = vel; };
	void SetRotationalVel(glm::vec3 rot) { rotationalVel = rot; };
	void setElasticity(float value) { elasticity = value; };
	void setFriction(float value) { friction = value; };
	void SetMass(float _mass) { mass = _mass; };
	void setKinematic(bool value) { isKinematic = value; };

private:
	Object* attachedObj;

	glm::vec3 momentum;
	glm::vec3 velocity;
	glm::vec3 force;
	glm::vec3 rotationalVel;

	glm::vec3 CalculateMomentum() { return mass * velocity; };
	
	void Drag(float deltaTime);

	int UpdateType = 0;
	void Euler(float deltaTime);
	void RungeKutta2(float deltaTime);
	void RungeKutta4(float deltaTime);
	void Vertlet(float deltaTime);

	bool isKinematic = true;
	bool gravityAffected = true;

	float elasticity, friction;
	float mass = 1;
};