#pragma once
#include "ObjectScript.h"
#include "Time.h"
#include "Input.h"
#include <glm/glm.hpp>

class Player : public ObjectScript
{
	using ObjectScript::ObjectScript;

public:
	SceneTime* time = SceneTime::getInstance();
	Input* input = Input::getInstance();
	void Update() override;
	void OnCollisionEnter(Object* collision) override;
	void KeyInput();

	glm::vec3 movement;
	bool canJump = true;
};