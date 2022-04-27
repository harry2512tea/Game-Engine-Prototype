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
	for (Object obj : objects)
	{
		obj.Update(DeltaTime);
	}
	//camPos = objects[2].GetPosition() + glm::vec3(0.0f, 2.0f, 10.0f);


	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i].UpdatePhysics(DeltaTime, objects, i);
	}

	//std::cout << objects[3].GetRigidbody()->GetVelocity().x, objects[3].GetRigidbody()->GetVelocity().y, objects[3].GetRigidbody()->GetVelocity().z;

	kin->Update(objects);
}

void Scene::DrawScene()
{
	cam = glm::mat4(1.0f);
	cam = glm::translate(cam, -camPos);
	cam = setCamRotation(cam);

	glEnable(GL_DEPTH_TEST);
	for (Object obj : objects)
	{
		obj.DrawObject(SceneShader, window, LightPos, LightCol, cam);
	}
	glDisable(GL_DEPTH_TEST);
}

void Scene::CreateLevel()
{
	objects.push_back(Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(0.0f, -5.0f, -20.0f), glm::vec3(0.0f), glm::vec3(0.5f)));
	objects.push_back(Object("Models/curuthers/curuthers.obj", SceneShader, glm::vec3(2, 0, -20)));
	objects.push_back(Object("Models/curuthers/curuthers.obj", SceneShader, glm::vec3(-2, 0, -20), glm::vec3(0, 90, 0)));
	objects.push_back(Object("Models/Ball/sphere.obj", "Models/Ball/WelcomeMatClear_diffuse.jpg", SceneShader, glm::vec3(-0, 4, -10)));

	objects[3].GetRigidbody()->SetColliderType(1);
	objects[3].GetRigidbody()->setKinematic(false);

	//objects[2].AddScript(new movement(&objects[2]));
}

glm::mat4 Scene::setCamRotation(glm::mat4 _cam)
{
	_cam = glm::rotate(_cam, glm::radians(-camRot.x), glm::vec3(1, 0, 0));
	_cam = glm::rotate(_cam, glm::radians(-camRot.y), glm::vec3(0, 1, 0));
	_cam = glm::rotate(_cam, glm::radians(-camRot.z), glm::vec3(0, 0, 1));

	return _cam;

}