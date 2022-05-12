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
	attachedObj->rotate(glm::vec3(0.0f, 1.0f, 0.0f));
	//KeyInput();
}

void movement::KeyInput()
{
	Input* input = Input::getInstance();
	if (input->GetAxis("spin1"))
	{
		attachedObj->rotate(glm::vec3(0.0f, 0.0f, 0.5f));
	}

	if (input->GetAxis("spin2"))
	{
		attachedObj->rotate(glm::vec3(0.0f, 0.0f, -0.5f));
	}
	
}