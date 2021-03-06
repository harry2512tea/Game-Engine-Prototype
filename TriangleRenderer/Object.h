#pragma once

#include <wavefront/wavefront.h>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <SDL2/SDL.h>
#include <list>
#include <vector>
//#include <glm/gtx/quaternion.hpp>

#include "Shader.h"
#include "ObjectScript.h"
#include "DynamicObject.h"
#include "Plane.h"

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
	void UpdatePhysics(float DeltaTime, std::vector<Object*>& objs, int address);
	void DrawObject(Shader& shad, SDL_Window *window, glm::vec3 lightPos, glm::vec3 lightCol, glm::mat4 cam);
	void StartScripts();

	void translation(glm::vec3 movement);
	void rotate(glm::vec3 _rotation);
	void AddScript(ObjectScript* _script);
	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetColliderType(int col) { colliderType = col; };

	// 0 = OBB
	// 1 = Sphere Collider
	int GetColliderType() { return colliderType; };
	float GetSphereRadius();
	DynamicObject* GetRigidbody() { return &Rigidbody; };
	std::vector<OBBPlane*>& GetPlanes() { return OBBPlanes; };
	glm::vec3 GetPosition();
	glm::quat GetRotation();


	glm::vec3 centerOffset, center, size, min, max;

private:


	int width, height;
	WfModel objectModel = { 0 };
	DynamicObject Rigidbody;
	glm::mat4 model;
	std::vector<glm::vec3> vertices;
	std::vector<ObjectScript*> scripts;
	glm::vec3 scale = glm::vec3(0.0f);
	glm::vec3 previousPos;
	glm::vec3 previousRot;
	glm::vec3 previousScale;
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	GLuint projectionLoc, modelLoc, viewLoc, lightLoc, lightColLoc;

	glm::mat4 setModelRotation(glm::mat4 model);
	GLuint GenTexture(const std::string& _texturePath);
	void GetVertices(const std::string& _modelPath);
	void calculateAABB();
	void calculateOBB();
	void UpdateCollider();

	//Colliders
	int colliderType = 0;
	bool isTrigger;

	//Sphere collider
	float colliderRadius;

	//Axis Aligned Bounding Box
	glm::vec3 initialMin, initialMax = glm::vec3(0.0f);
	std::vector<AABBPlane*> Planes;

	//Oriented Bounding Box
	glm::vec3 OBBinitialMin, OBBinitialMax = glm::vec3(0.0f);
	glm::quat rotationQuat;
	std::vector<OBBPlane*> OBBPlanes;
};
