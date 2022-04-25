#pragma once
#include "ObjectScript.h"

class movement : public ObjectScript
{
	using ObjectScript::ObjectScript;
public:

	void Start() override;
	void Update() override;

	void KeyInput();
};