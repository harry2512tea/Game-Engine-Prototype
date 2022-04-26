#pragma once

#include <wavefront/wavefront.h>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <list>
#include <vector>

#include "Shader.h"
#include "ObjectScript.h"
#include "Kinematic.h"

class Object
{
public:
	//main functions of the object
	Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad, glm::vec3 pos, glm::vec3 rot, glm::vec3 _scale);
	Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad, glm::vec3 pos, glm::vec3 rot);
	Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad, glm::vec3 pos);
	Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad);

	Object(const std::string& _modelPath, Shader shad, glm::vec3 pos, glm::vec3 rot, glm::vec3 _scale);
	Object(const std::string& _modelPath, Shader shad, glm::vec3 pos, glm::vec3 rot);
	Object(const std::string& _modelPath, Shader shad, glm::vec3 pos);
	Object(const std::string& _modelPath, Shader shad);
	~Object();

	void Update(float DeltaTime);
	void DrawObject(Shader& shad, SDL_Window *window, glm::vec3 lightPos, glm::vec3 lightCol, glm::mat4 cam);

	void translate(glm::vec3 translation);
	void rotate(glm::vec3 _rotation);

	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);

	void AddScript(ObjectScript* _script);
	void StartScripts();

	int GetColliderType();
	float GetSphereRadius();
	void UpdatePhysics(float DeltaTime, std::vector<Object>& objs, int address);

	Kinematic* GetRigidbody();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 centerOffset, center, size, min, max;

private:
	
	Kinematic Rigidbody;

	GLuint GenTexture(const std::string& _texturePath);

	void GetVertices(const std::string& _modelPath);
	void calculateAABB();
	
	std::vector < glm::vec3> vertices;
	std::vector<ObjectScript*> scripts;
	int ScriptNo = 0;
	WfModel objectModel = { 0 };
	glm::vec3 scale;
	glm::vec3 position;
	glm::vec3 rotation;

	//bounding boxes
	glm::vec3 minOffset, maxOffset;
	float colliderRadius;
	
	
	GLuint projectionLoc, modelLoc, viewLoc, lightLoc, lightColLoc;
	int width, height;
	glm::mat4 setModelRotation(glm::mat4 model);
};