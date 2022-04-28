#pragma once
#include <iostream>

#include "movement.h"
#include "glm/glm.hpp"
#include "Object.h"
#include "Input.h"

void movement::Start()
{

}

void movement::Update()
{
	attachedObj->translation(glm::vec3(0.1f, 0.0f, 0.0f));
	if (attachedObj->GetPosition().x > 10)
	{
		attachedObj->SetPosition(glm::vec3(-10.0f, 1.0f, -20.0f));
	}
	KeyInput();

	//std::cout << "Position:" << attachedObj->GetPosition().x << " " << attachedObj->GetPosition().y << " " << attachedObj->GetPosition().z << std::endl;
	//std::cout << "Center:" << attachedObj->center.x << " " << attachedObj->center.y << " " << attachedObj->center.z << std::endl;
}

void movement::KeyInput()
{
	Input* input = Input::getInstance();
	if (input->GetAxis("Forward"))
	{
		std::cout << "Forward" << std::endl;
	}

	if (input->GetAxis("Back"))
	{
		std::cout << "Back" << std::endl;
	}

	if (input->GetAxis("Left"))
	{
		std::cout << "Left" << std::endl;
	}

	if (input->GetAxis("Right"))
	{
		std::cout << "Right" << std::endl;
	}

	if (input->GetAxis("Up"))
	{
		std::cout << "Up" << std::endl;
	}
	
}