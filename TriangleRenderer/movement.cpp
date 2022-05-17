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
	float movementspeed = 1.0f;
	glm::vec3 direction = glm::vec3(-1.0f, 0.0f, 0.0f);
	
	attachedObj->translation(direction);
	if (attachedObj->GetPosition().x < -126)
	{
		glm::vec3 pos = attachedObj->GetPosition();
		attachedObj->SetPosition(glm::vec3(134.0f, -6.0f, 0.0f));
	}
	//KeyInput();
}

void movement::KeyInput()
{
	Input* input = Input::getInstance();
}