#include "Scene.h"

#include <glm/ext.hpp>
#include <GL/glew.h>
#include <iostream>

Scene::Scene(glm::vec3 light, SDL_Window *_window) 
	: SceneShader("shaders/light.vert", "shaders/light.frag")
{
	LightPos = light;
	window = _window;
	camPos = glm::vec3(0.0f, 4.0f, 0.0f);
	camRot = glm::vec3(-10.0f, 0.0f, 0.0f);
	LightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	
	CreateLevel();
}

void Scene::updateObjects(float DeltaTime)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(DeltaTime);
	}
	//camPos = objects[2].GetPosition() + glm::vec3(0.0f, 2.0f, 10.0f);


	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->UpdatePhysics(DeltaTime, objects, i);
	}

	//std::cout << objects[3].GetRigidbody()->GetVelocity().x, objects[3].GetRigidbody()->GetVelocity().y, objects[3].GetRigidbody()->GetVelocity().z;

	kin->Update(objects);

	Input* input = Input::getInstance();
	if (input->GetAxis("Forward"))
	{
		camPos += glm::vec3(0.0f, 0.0f, -0.5f);
	}

	if (input->GetAxis("Back"))
	{
		camPos += glm::vec3(0.0f, 0.0f, 0.5f);
	}

	if (input->GetAxis("Left"))
	{
		camPos += glm::vec3(-0.5f, 0.0f, 0.0f);
	}

	if (input->GetAxis("Right"))
	{
		camPos += glm::vec3(0.5f, 0.0f, 0.0f);
	}

	if (input->GetAxis("Up"))
	{
		camPos += glm::vec3(0.0f, 0.5f, 0.0f);
	}
	if (input->GetAxis("Down"))
	{
		camPos += glm::vec3(0.0f, -0.5f, 0.0f);
	}
	if (input->GetAxis("RotLeft"))
	{
		camRot += glm::vec3(0.0f, 2.0f, 0.0f);
	}
	if (input->GetAxis("RotRight"))
	{
		camRot += glm::vec3(0.0f, -2.0f, 0.0f);
	}
}

void Scene::DrawScene()
{
	cam = glm::mat4(1.0f);
	cam = glm::translate(cam, -camPos);
	cam = setCamRotation(cam);

	glEnable(GL_DEPTH_TEST);
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->DrawObject(SceneShader, window, LightPos, LightCol, cam);
	}
	glDisable(GL_DEPTH_TEST);
}

void Scene::CreateLevel()
{
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(0.0f, -5.0f, -20.0f), glm::vec3(0.0f), glm::vec3(0.5f)));
	objects.push_back(new Object("Models/curuthers/curuthers.obj", SceneShader, glm::vec3(2, 4, -20)));
	objects.push_back(new Object("Models/curuthers/curuthers.obj", SceneShader, glm::vec3(-2, 4, -20), glm::vec3(0, 90, 0)));
	objects.push_back(new Object("Models/Ball/sphere.obj", "Models/Ball/WelcomeMatClear_diffuse.jpg", SceneShader, glm::vec3(-0, 5, -10)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(0.0f, 8.0f, -20.0f), glm::vec3(0.0f), glm::vec3(0.5f)));

	objects[3]->GetRigidbody()->SetColliderType(1);
	objects[3]->GetRigidbody()->setKinematic(false);

	//objects[2]->AddScript(new movement(objects[2]));
}

glm::mat4 Scene::setCamRotation(glm::mat4 _cam)
{
	_cam = glm::rotate(_cam, glm::radians(-camRot.x), glm::vec3(1, 0, 0));
	_cam = glm::rotate(_cam, glm::radians(-camRot.y), glm::vec3(0, 1, 0));
	_cam = glm::rotate(_cam, glm::radians(-camRot.z), glm::vec3(0, 0, 1));

	return _cam;

}