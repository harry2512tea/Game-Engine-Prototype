#pragma once
#include "ObjectScript.h"
#include "Time.h"
#include "Input.h"
#include <glm/glm.hpp>

class Avoid : public ObjectScript
{
	using ObjectScript::ObjectScript;

public:
	SceneTime* time = SceneTime::getInstance();
	Input* input = Input::getInstance();
	void Update() override;
};