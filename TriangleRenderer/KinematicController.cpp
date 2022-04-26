#include "KinematicController.h"

KinematicController* KinematicController::instance = nullptr;

KinematicController* KinematicController::getInstance()
{
	if (!instance)
	{
		instance = new KinematicController();
	}

	return instance;
}

void KinematicController::CheckGeneralCollisions(std::vector<Object>& objs)
{
	for (int i = 0; i < objs.size(); i++)
	{
		for (int O = i + 1; O < objs.size(); O++)
		{
			if (checkCollision(objs[i], objs[O]))
			{
				CheckPreciseCollision(objs[i], objs[O]);
			}
		}
	}
}

bool KinematicController::checkCollision(Object& obj1, Object& obj2)
{
	float x, y, z, dist;
	switch (obj1.GetColliderType())
	{
	case 0:
		switch (obj2.GetColliderType())
		{
		case 0:
			return (obj1.min.x <= obj2.max.x && obj1.max.x >= obj2.max.x) &&
				(obj1.min.y <= obj2.max.y && obj1.max.y >= obj2.max.y) &&
				(obj1.min.z <= obj2.max.z && obj1.max.z >= obj2.max.z);
			break;

		case 1:
			glm::vec3 sphere = obj2.GetPosition();
			x = fmaxf(obj1.min.x, fminf(sphere.x, obj1.max.x));
			y = fmaxf(obj1.min.y, fminf(sphere.y, obj1.max.y));
			z = fmaxf(obj1.min.z, fminf(sphere.z, obj1.max.z));

			dist = sqrt((x - sphere.x) * (x - sphere.x) +
				(y - sphere.y) * (y - sphere.y) +
				(z - sphere.z) * (x - sphere.z)
			);

			return dist < obj2.GetSphereRadius();
			break;
		}
		break;

	case 1:
		switch (obj2.GetColliderType())
		{
		case 0:
			glm::vec3 sphere = obj1.GetPosition();
			x = fmaxf(obj2.min.x, fminf(sphere.x, obj2.max.x));
			y = fmaxf(obj2.min.y, fminf(sphere.y, obj2.max.y));
			z = fmaxf(obj2.min.z, fminf(sphere.z, obj2.max.z));

			dist = sqrt((x - sphere.x) * (x - sphere.x) +
				(y - sphere.y) * (y - sphere.y) +
				(z - sphere.z) * (x - sphere.z)
			);

			return dist < obj1.GetSphereRadius();
			break;

		case 1:
			glm::vec3 a = obj1.GetPosition();
			glm::vec3 b = obj2.GetPosition();

			dist = sqrt((a.x - b.x) * (a.x - b.x) +
				(a.y - b.y) * (a.y - b.y) +
				(a.z - b.z) * (a.z - b.z)
			);

			return dist < (obj1.GetSphereRadius() + obj2.GetSphereRadius());
			break;

		}
		break;
	}
	return false;
}

void KinematicController::CheckPreciseCollision(Object& obj1, Object& obj2)
{
}

void KinematicController::DoWallCollision(glm::vec3 wallNormal, Kinematic* Rb)
{

}

void KinematicController::DoMomentumCollision()
{
}


