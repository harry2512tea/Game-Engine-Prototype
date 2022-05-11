#pragma warning(disable : 4996)
#include "Scene.h"

#include <glm/ext.hpp>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

Scene::Scene(SDL_Window *_window, const std::string& filePath)
	: SceneShader("shaders/light.vert", "shaders/light.frag")
{
	//importing data from the text file, setting up the temporary variables
	std::string skip;
	std::string temp;

	//opening the specified file
	std::ifstream file(filePath.c_str());

	//running through the whole file
	while (!file.eof())
	{
		//skipping past the junk data
		std::getline(file, skip, '~');
		//storing the required data
		std::getline(file, temp);
		//adding the data to a list
		Data.push_back(temp);
	}
	//closing the file to prevent memory leaks
	file.close();
	window = _window;
	
	//initialising the level
	CreateLevel(Data);
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

	kin->Update(objects, DeltaTime);

	Input* input = Input::getInstance();

	glm::quat camRotation = glm::quat(glm::radians(-camRot));
	if (input->GetAxis("Start"))
	{
		for (int i = 0; i < physicsObjects.size(); i++)
		{
			objects[i]->GetRigidbody()->setKinematic(false);
		}
	}

	if (input->GetAxis("ramps"))
	{
		for (int i = 0; i < 3; i++)
		{
			objects[i]->GetRigidbody()->setKinematic(false);
		}
	}
	if (input->GetAxis("collide"))
	{
		for (int i = 3; i < 5; i++)
		{
			objects[i]->GetRigidbody()->setKinematic(false);
		}
	}
	if (input->GetAxis("bounce"))
	{
		for (int i = 5; i < 8; i++)
		{
			objects[i]->GetRigidbody()->setKinematic(false);
		}
	}
	if (input->GetAxis("spin"))
	{
		for (int i = 8; i < 10; i++)
		{
			objects[i]->GetRigidbody()->setKinematic(false);
		}
	}



	if (input->GetAxis("Forward"))
	{
		camPos += (glm::vec3(0.0f, 0.0f, -0.5f) * camRotation);
	}

	if (input->GetAxis("Back"))
	{
		camPos += (glm::vec3(0.0f, 0.0f, 0.5f) * camRotation);
	}

	if (input->GetAxis("Left"))
	{
		camPos += (glm::vec3(-0.5f, 0.0f, 0.0f) * camRotation);
	}

	if (input->GetAxis("Right"))
	{
		camPos += (glm::vec3(0.5f, 0.0f, 0.0f) * camRotation);
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
	cam = setCamRotation(cam);
	cam = glm::translate(cam, -camPos);
	

	glEnable(GL_DEPTH_TEST);
	for (int i = 0; i < objects.size() - 1; i++)
	{
		objects[i]->DrawObject(SceneShader, window, LightPos, LightCol, cam);
	}
	glDisable(GL_DEPTH_TEST);
}

void Scene::CreateLevel(std::vector<std::string>& data)
{
	//importing the data from the file
	camPos = ImportVectorData(data[0]);
	camRot = ImportVectorData(data[1]);
	LightPos = ImportVectorData(data[2]);
	LightCol = ImportVectorData(data[3]);
	ObjectController::getInstance()->SetGravity(ImportVectorData(data[4]));
	ObjectController::getInstance()->SetDensity(std::stof(data[5].c_str()));
	std::string ObjectList = data[6];

	

	//initialising the physics objects
	CreatePhysicsObjects(ObjectList);
	//objects.push_back(new Object("Models/Ball/sphere.obj", "Models/Ball/WelcomeMatClear_diffuse.jpg", SceneShader, glm::vec3(-8, 5, -10)));
	//objects.push_back(new Object("Models/Ball/sphere.obj", "Models/Ball/WelcomeMatClear_diffuse.jpg", SceneShader, glm::vec3(0, 5, -10)));

	//creating the rest of the scene
	//objects.push_back(new Object("Models/curuthers/curuthers.obj", SceneShader, glm::vec3(2, 4, -30), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(1.0f)));
	//objects.push_back(new Object("Models/curuthers/curuthers.obj", SceneShader, glm::vec3(-2, 4, -30)));


	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(0.0f, -7.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(0.0f, 15.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(0.0f, 0.0f, -30.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.5f, 0.5f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(-65.0f, -7.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 20.0f, 1.0f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(40.0f, -7.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 20.0f, 1.0f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(23.0f, 0.0f, -10.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.5f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(23.0f, 0.0f, 10.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.5f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(-40.0f, 0.0f, -10.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.5f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(-40.0f, 0.0f, 10.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.5f)));

	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(14.0f, -3.0f, -25.0f), glm::vec3(0.0f, 0.0f, -45.0f), glm::vec3(0.1f, 0.5f, 0.1f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(14.0f, -3.5f, -20.0f), glm::vec3(0.0f, 0.0f, -30.0f), glm::vec3(0.1f, 0.5f, 0.1f)));
	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(14.0f, -4.5f, -15.0f), glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.1f, 0.5f, 0.1f)));

	objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(0.0f, -5.0f, -23.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 10.0f, 0.4f)));
	//objects.push_back(new Object("Models/WelcomeMat3DModel/WelcomeMatOBJ.obj", "Models/WelcomeMat3DModel/Textures/WelcomeMat_diffuse.jpg", SceneShader, glm::vec3(40.0f, -6.0f, -10.0f), glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.1f, 0.5f, 0.1f)));
	//objects.push_back(new Object("Models/Prism/obamaprisme.obj", "Models/Prism/obama_prime.jpg", SceneShader, glm::vec3(4.0f, 4.0f, -20.0f), glm::vec3(-0.0f, 0.0f, 0.0f), glm::vec3(5.0f)));

	//Attaching custom scripts to specified objects
	//objects.front()->AddScript(new movement(objects.front()));
}

glm::mat4 Scene::setCamRotation(glm::mat4 _cam)
{
	//creating a rotation matrix by rotating about each axis
	_cam = glm::rotate(_cam, glm::radians(-camRot.x), glm::vec3(1, 0, 0));
	_cam = glm::rotate(_cam, glm::radians(-camRot.y), glm::vec3(0, 1, 0));
	_cam = glm::rotate(_cam, glm::radians(-camRot.z), glm::vec3(0, 0, 1));

	//returning the rotation matrix
	return _cam;

}

glm::vec3 Scene::ImportVectorData(const std::string& data)
{
	//extracting data from a string
	std::vector<float> tempData;
	//converting the string to a const char array
	char* temp = new char[data.length() + 1];

	//copying the raw data to the array
	strcpy(temp, data.c_str());

	//Getting the first value
	char* Data = strtok(temp, ",");
	
	//running through all the values in the raw data
	while (Data != NULL)
	{
		//appending the values to a list
		tempData.push_back(std::stof(Data));
		//getting the next value
		Data = strtok(NULL, ",");
	}
	
	//returning the extracted data
	return glm::vec3(tempData[0], tempData[1], tempData[2]);
}

void Scene::CreatePhysicsObjects(const std::string& _filePath)
{
	std::string temp;
	std::vector<std::string> objectPaths;

	//opening the list of physics object paths
	std::ifstream doc(_filePath.c_str());

	//checking to see if the file opened
	if (!doc)
	{
		throw std::runtime_error("file failed");
	}
	
	//running through the whole document
	while (!doc.eof())
	{
		//splitting the document up into separate file paths
		std::getline(doc, temp);
		//appending each file path to a list
		objectPaths.push_back(temp);
	}
	//closing the file to prevent memory leaks
	doc.close();

	//creating each physics object in the list
	for (int i = 0; i < objectPaths.size(); i++)
	{
		CreateObject(objectPaths[i]);
	}
}

void Scene::CreateObject(const std::string& filePath)
{
	std::string skip;
	std::string temp;
	std::ifstream file;
	file.open(filePath.c_str());
	std::vector<std::string> data;

	//running through the document
	while (!file.eof())
	{
		//skipping junk data
		std::getline(file, skip, '~');

		//retrieving and appending the required data
		std::getline(file, temp);
		data.push_back(temp);
	}
	//closing the file to prevent memory leaks
	file.close();

	//appending the extracted data
	objects.push_back(new Object(data[0].c_str(), data[1].c_str(), SceneShader, ImportVectorData(data[2]), ImportVectorData(data[3]), ImportVectorData(data[4])));
	objects.back()->SetColliderType(std::stoi(data[5]));
	objects.back()->GetRigidbody()->setElasticity(std::stof(data[6]));
	objects.back()->GetRigidbody()->setFriction(std::stof(data[7]));
	objects.back()->GetRigidbody()->SetVelocity(ImportVectorData(data[8]));
	objects.back()->GetRigidbody()->SetRotationalVel(ImportVectorData(data[9]));
	physicsObjects.push_back(objects.back());
}