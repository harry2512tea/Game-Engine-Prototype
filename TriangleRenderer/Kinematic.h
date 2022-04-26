#pragma once
#include <vector>
#include "glm/glm.hpp"

class Object;
class KinematicController;

class Kinematic
{
public:
	Kinematic(Object* obj);
	void Update(float DeltaTime, std::vector<Object>& objs, int address);
	
	void setKinematic(bool value);
	bool CheckCollision(Object& obj);
	float GetMass();

	int GetColliderType();
	void SetColliderType(int col);

private:
	float CalculateMomentum();
	
	Object* attachedObj;
	bool isKinematic = false;
	int colliderType;
	float mass = 1;
	float momentum;
	glm::vec3 velocity;

};