#pragma once

class Object;

class ObjectScript
{
public:
	explicit ObjectScript(Object* obj) : attachedObj(obj)
	{}
	virtual void Update() {};
	virtual void Start() {};
	virtual void OnCollisionEnter(Object* collision) {};
	virtual void OnTriggerEnter(Object* collision) {};
protected:
	Object* attachedObj;
};