#pragma once
#include <vector>
#include "glm/glm.hpp"

class Object;

class Kinematic
{
public:
	Kinematic(Object* obj);
	void Update(float DeltaTime, std::vector<Object>& objs, int address);
	
	
	bool CheckCollision(Object& obj);

	float GetMass() { return mass; };
	void SetMass(float _mass) { mass = _mass; };

	glm::vec3 GetMomentum() { return momentum; };
	glm::vec3 GetVelocity() { return velocity; };
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
	int colliderType;
	float mass = 1;
	glm::vec3 momentum;
	glm::vec3 velocity;

};