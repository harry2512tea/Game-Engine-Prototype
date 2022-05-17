#pragma once
#include "ObjectScript.h"
#include "Time.h"

class movement : public ObjectScript
{
	using ObjectScript::ObjectScript;
public:
	SceneTime* time = SceneTime::getInstance();
	void Start() override;
	void Update() override;

	void KeyInput();
};