#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <list>
#include <vector>
//#include <glm/gtx/quaternion.hpp>

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f));
	void SetRotation(glm::vec3 Rotation);
	void Rotate(glm::vec3 Rotation);
	void SetPosition(glm::vec3 _Position) { Position = _Position; };
	void Translate(glm::vec3 Translation) { Position += Translation; };
	void SetNearClip(float near) { nearClip = near; };
	void SetFarClip(float far) { farClip = far; };

	float GetNearClip() { return nearClip; };
	float GetFarClip() { return farClip; };
	glm::vec3 GetPosition() { return Position; };
	glm::vec3 GetRotation() { return Rotation; };
	glm::mat4 CreateViewMatrix();
private:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::quat RotationQuat;

	float farClip = 100.f, nearClip = 0.1f;

	glm::vec3 CheckRotation(glm::vec3 _rotation);
	glm::quat DoRotation(glm::vec3 Euler);
};