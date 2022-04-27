#pragma once
//c++ Libraries
#include <list>
#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

//Project header files
#include "Object.h"
#include "Shader.h"
#include "ObjectScript.h"
#include "movement.h"
#include "KinematicController.h"
#include "Lights.h"

class Scene
{
public:
	Scene(glm::vec3 light, SDL_Window *_window);
	void updateObjects(float DeltaTime);
	void DrawScene();

	glm::mat4 setCamRotation(glm::mat4 _cam);

private:
	KinematicController* kin = KinematicController::getInstance();
	std::vector<Object> objects;
	std::vector<DirectionalLight> dirLights;
	std::vector<PointLight>pointLights;
	glm::vec3 camPos, camRot;
	glm::mat4 cam;
	SDL_Window *window;
	Shader SceneShader;

	void CreateLevel();
};