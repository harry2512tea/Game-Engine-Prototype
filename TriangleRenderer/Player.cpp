#include "Player.h"
#include "Object.h"


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

void Player::OnCollisionEnter()
{
	if (input->GetAxis("Up") && canJump)
	{
		canJump = false;
		attachedObj->GetRigidbody()->AddForce(glm::vec3(0.0f, 20.0f, 0.0f), VelocityChange);
	}
}

void Player::KeyInput()
{
	if (input->GetAxis("Forward"))
	{
		attachedObj->translation(glm::vec3(0.0f, 0.0f, -1.0f));
	}
	if (input->GetAxis("Back"))
	{
		attachedObj->translation(glm::vec3(0.0f, 0.0f, 1.0f));
	}
}