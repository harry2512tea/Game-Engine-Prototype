#pragma once
#include <string>

class Object;

enum Type
{
	Default,
	Transform,
	renderer,
	collider,
	script
};

class Component
{
public:
	Component(Object* obj) : attachedObj(obj)
	{};
	virtual void Update() {};
	virtual Type GetType() { return type; };

protected:
	Object* attachedObj;
	Type type = Default;
};