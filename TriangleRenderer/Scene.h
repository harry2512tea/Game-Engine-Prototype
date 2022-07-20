#pragma once
//c++ Libraries
#include <list>
#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <string>

//Project header files
#include "Camera.h"
#include "Object.h"
#include "Shader.h"
#include "ObjectScript.h"
#include "movement.h"
#include "Player.h"
#include "ObjectController.h"
#include "Input.h"
#include "Avoid.h"

class Scene
{
public:
	Scene(SDL_Window *_window, const std::string& filePath);
	void updateObjects(float DeltaTime);
	void DrawScene();

private:
	std::string ObjectFile;
	glm::vec3 ImportVectorData(const std::string& data);
	std::vector<std::string> Data;
	ObjectController* kin = ObjectController::getInstance();
	std::vector<Object*> objects;
	std::vector<Object*> physicsObjects;
	std::vector<Camera*> Cameras;
	glm::vec3 LightPos, LightCol;
	glm::mat4 cam;
	SDL_Window *window;
	Shader SceneShader;
	Camera MainCam;

	void CreateLevel(std::vector<std::string> &data);
	void CreatePhysicsObjects(const std::string& filePath);
	void CreateObject(const std::string& filePath);
};