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
	glm::vec3 direction = glm::vec3(-1.0f, 0.0f, 0.0f);
	
	attachedObj->translation(direction * movementspeed * time->GetDeltaTime());
	if (attachedObj->GetPosition().x < -126)
	{
		glm::vec3 pos = attachedObj->GetPosition();
		attachedObj->SetPosition(glm::vec3(133.0f, -6.0f, 0.0f));
	}

	movementspeed += time->GetDeltaTime();
	movementspeed = round(movementspeed * 10) / 10;
	//KeyInput();
}

void movement::KeyInput()
{
	Input* input = Input::getInstance();
}