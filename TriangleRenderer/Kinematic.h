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

class Kinematic
{
public:
	Kinematic(Object* obj);
	void Update(float DeltaTime);
	

	float GetMass() { return mass; };
	void SetMass(float _mass) { mass = _mass; };

	glm::vec3 GetMomentum() { return momentum; };
	glm::vec3 GetVelocity() { return velocity; };

	void AddForce(glm::vec3 Force, ForceMode Mode);
	void AddVelocity(glm::vec3 vel) { velocity += vel; };
	void SetVelocity(glm::vec3 vel) { velocity = vel; };

	bool getKinematic() { return isKinematic; };
	void setKinematic(bool value) { isKinematic = value; };

	int GetColliderType();
	void SetColliderType(int col);

private:
	glm::vec3 CalculateMomentum();
	
	
	Object* attachedObj;
	bool isKinematic = true;
	int colliderType = 0;
	float mass = 1;
	glm::vec3 momentum;
	glm::vec3 velocity;

};