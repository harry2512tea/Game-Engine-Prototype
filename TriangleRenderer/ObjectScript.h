#pragma once

class Object;

class ObjectScript
{
public:
	explicit ObjectScript(Object* obj) : attachedObj(obj)
	{}
	virtual void Update() {};
	virtual void Start() {};
	virtual void OnCollisionEnter() {};
	virtual void OnTriggerEnter() {};
protected:
	Object* attachedObj;
};