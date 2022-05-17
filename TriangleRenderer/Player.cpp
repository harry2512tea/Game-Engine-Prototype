#include "Player.h"
#include "Object.h"
#include <iostream>

void Player::Update()
{
	if (!canJump)
	{
		if (!input->GetAxis("up"))
		{
			canJump = true;
		}
	}
	KeyInput();
}

void Player::OnCollisionEnter(Object* collision)
{
	if (input->GetAxis("Up") && canJump)
	{
		canJump = false;
		attachedObj->GetRigidbody()->AddForce(glm::vec3(0.0f, 20.0f, 0.0f), VelocityChange);
	}
}

void Player::KeyInput()
{
	glm::vec3 rotation = glm::degrees(glm::eulerAngles(attachedObj->GetRotation()));
	if (input->GetAxis("Forward") && !input->GetAxis("Back"))
	{
		attachedObj->translation(glm::vec3(0.0f, 0.0f, -10.0f) * time->GetDeltaTime());
		attachedObj->SetRotation(glm::vec3(0.0f, -180.0f, 0.0f));
	}
	else if (input->GetAxis("Back"))
	{
		attachedObj->translation(glm::vec3(0.0f, 0.0f, 10.0f) * time->GetDeltaTime());
		attachedObj->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		
		attachedObj->SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));
	}
}