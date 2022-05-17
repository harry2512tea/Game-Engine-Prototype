#include "Avoid.h"
#include "Object.h"

void Avoid::Update()
{
	attachedObj->rotate(glm::vec3(0.0f, 1.0f, 0.0f));
}