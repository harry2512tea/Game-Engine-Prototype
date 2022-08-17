#pragma once
#include "Component.h"
#include <vector>
#include <glm/glm.hpp>

class Renderer : public Component
{
public:
	Renderer(Object* obj);
	std::vector<glm::vec3>* getVertices() { return &vertices; };
protected:
	std::vector<glm::vec3> vertices;
};