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

#include "Camera.h"
#include "Shader.h"
#include "ObjectScript.h"
#include "DynamicObject.h"
#include "Plane.h"

class Object
{
public:
	//main functions of the object
	Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 _scale = glm::vec3(1.0f));

	Object(const std::string& _modelPath, Shader shad, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 _scale = glm::vec3(1.0f));
	~Object();

	void Update(float DeltaTime);
	void UpdatePhysics(float DeltaTime, std::vector<Object*>& objs, int address);
	void DrawObject(Shader& shad, SDL_Window *window, glm::vec3 lightPos, glm::vec3 lightCol, Camera& cam);
	void StartScripts();
	void EnterTrigger(Object* collision);
	void EnterCollision(Object* collision);

	void translation(glm::vec3 movement);
	void rotate(glm::vec3 _rotation);
	void AddScript(ObjectScript* _script);
	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetColliderType(int col) { colliderType = col; };
	void SetTrigger(bool value) { isTrigger = value; };
	void SetSphereRadius(float value) { colliderRadius = value; };

	// 0 = OBB
	// 1 = Sphere Collider
	int GetColliderType() { return colliderType; };
	bool GetTrigger() { return isTrigger; };
	float GetSphereRadius() { return colliderRadius; };
	DynamicObject* GetRigidbody() { return &Rigidbody; };
	std::vector<OBBPlane*>& GetPlanes() { return OBBPlanes; };
	glm::vec3 GetPosition() { return position; };
	glm::quat GetRotation() { return rotationQuat; };


	glm::vec3 centerOffset, center, size, min, max;

private:


	int width, height;
	WfModel objectModel = { 0 };
	DynamicObject Rigidbody;
	glm::mat4 model, rot;
	std::vector<glm::vec3> vertices;
	std::vector<ObjectScript*> scripts;
	glm::vec3 scale = glm::vec3(0.0f);
	glm::vec3 previousPos;
	glm::vec3 previousRot;
	glm::vec3 previousScale;
	glm::vec3 radRot;
	
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	GLuint projectionLoc, modelLoc, viewLoc, lightLoc, lightColLoc, viewPosLoc;

	glm::mat4 setModelRotation(glm::mat4 model);
	GLuint GenTexture(const std::string& _texturePath);
	void GetVertices(const std::string& _modelPath);
	void calculateAABB();
	void calculateOBB();
	void UpdateCollider();
	glm::vec3 CheckRotation(glm::vec3 _rotation);

	glm::quat DoRotation(glm::vec3 Euler);

	void GetUniforms(Shader shad);

	//Colliders
	int colliderType = 0;
	bool isTrigger;
	glm::vec3 colliderOffset;

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
