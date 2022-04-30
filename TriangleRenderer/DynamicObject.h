#pragma once
#include <vector>
#include "glm/glm.hpp"
#include <iostream>

class Object;
class KinematicController;

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
	

	float GetMass() { return mass; };
	void SetMass(float _mass) { mass = _mass; };

	glm::vec3 GetMomentum() { return momentum; };
	glm::vec3 GetVelocity() { return velocity; };

	void AddForce(glm::vec3 Force, ForceMode Mode);
	void AddVelocity(glm::vec3 vel) { velocity += vel; };
	void SetVelocity(glm::vec3 vel) { velocity = vel; };
	void SetRotationalVel(glm::vec3 rot) { rotationalVel = rot; };
	glm::vec3 GetRotVel() { return rotationalVel; };

	float GetElasticity() { return elasticity; };
	void setElasticity(float value) { elasticity = value; };

	float GetFriction() { return friction; };
	void setFriction(float value) { friction = value; };

	bool getKinematic() { return isKinematic; };
	void setKinematic(bool value) { isKinematic = value; };

	int GetColliderType();
	void SetColliderType(int col);

private:
	glm::vec3 CalculateMomentum();
	
	void Euler(float deltaTime);
	void RungeKutta4(float deltaTime);
	
	Object* attachedObj;
	bool isKinematic = true;
	bool gravityAffected = true;
	int colliderType = 0;
	float elasticity, friction;
	float mass = 1;
	glm::vec3 momentum;
	glm::vec3 velocity;
	glm::vec3 force;
	glm::vec3 rotationalVel;

};