#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <SDL2/SDL.h>
#include <list>
#include <vector>

class Camera
{
public:

private:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::quat RotationQuat;

	glm::vec3 CheckRotation(glm::vec3 _rotation);
};