#pragma once
#include <glm/glm.hpp>

struct PointLight
{
	PointLight(glm::vec3 Position = glm::vec3(0.0f)) { position = Position; };
	glm::vec3 position;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	glm::vec3 ambient = glm::vec3(0.05f);
	glm::vec3 diffuse = glm::vec3(0.8f);
	glm::vec3 specular = glm::vec3(1.0f);
};

struct DirectionalLight
{
	DirectionalLight(glm::vec3 Direction) { direction = Direction; };
	glm::vec3 direction;

	glm::vec3 ambient = glm::vec3(0.05f);
	glm::vec3 diffuse = glm::vec3(0.8f);
	glm::vec3 specular = glm::vec3(1.0f);
};