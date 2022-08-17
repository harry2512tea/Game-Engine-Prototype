#include "Collider.h"
#include "Object.h"
#include "Renderer.h"
#include <vector>


Collider::Collider(Object* obj) : Component(obj)
{
	type = collider;
}

void Collider::UpdateAABB()
{
	if (attachedObj->HasComponent(renderer))
	{
		std::vector<glm::vec3>* vertices = dynamic_cast<Renderer*>(attachedObj->GetComponent(renderer))->getVertices();
	}
	
}