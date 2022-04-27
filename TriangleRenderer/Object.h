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
#include "Plane.h"
#include "Lights.h"

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
	void DrawObject(Shader& shad, SDL_Window *window, std::vector<DirectionalLight>& dirLights, std::vector<PointLight>& pointLights, glm::mat4 cam);

	void translation(glm::vec3 movement);
	void rotate(glm::vec3 _rotation);

	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);

	void AddScript(ObjectScript* _script);
	void StartScripts();

	int GetColliderType();
	float GetSphereRadius();
	void UpdatePhysics(float DeltaTime, std::vector<Object>& objs, int address);

	Kinematic* GetRigidbody() { return &Rigidbody; };

	std::vector<Plane*>& GetPlanes() { return Planes; };

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 centerOffset, center, size, min, max;

private:
	
	Kinematic Rigidbody;

	GLuint GenTexture(const std::string& _texturePath);

	void GetVertices(const std::string& _modelPath);
	void calculateAABB();
	void GetUniformLocs(Shader shad);
	
	std::vector<glm::vec3> vertices;
	std::vector<ObjectScript*> scripts;
	std::vector<Plane*> Planes;
	int ScriptNo = 0;
	WfModel objectModel = { 0 };
	glm::vec3 scale = glm::vec3(0.0f);
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);

	//bounding boxes
	glm::vec3 minOffset, maxOffset = glm::vec3(0.0f);
	float colliderRadius;
	
	void SetupLights(Shader shad, std::vector<DirectionalLight>& dirLights, std::vector<PointLight>& pointLights);
	
	GLuint projectionLoc, modelLoc, viewLoc, PointNoLoc, DirNoLoc;
	int width, height;
	glm::mat4 setModelRotation(glm::mat4 model);

};