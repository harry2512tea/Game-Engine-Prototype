#include "KinematicController.h"
#include "Plane.h"
#include <vector>
#include <iostream>

KinematicController* KinematicController::instance = nullptr;

KinematicController* KinematicController::getInstance()
{
	if (!instance)
	{
		instance = new KinematicController();
	}

	return instance;
}

void KinematicController::CheckGeneralCollisions(std::vector<Object*>& objs)
{
	for (int i = 0; i < objs.size(); i++)
	{
		for (int O = i + 1; O < objs.size(); O++)
		{
			if (!objs[i]->GetRigidbody()->getKinematic() || !objs[O]->GetRigidbody()->getKinematic())
			{
				if (checkCollision(objs[i], objs[O]))
				{
					std::cout << "Collision " << i << " " << O << std::endl;
					CheckPreciseCollision(objs[i], objs[O]);
				}
			}
		}
	}
}

bool KinematicController::checkCollision(Object* obj1, Object* obj2)
{
	float x, y, z, dist;
	glm::vec3 sphere;
	switch (obj1->GetColliderType())
	{
	case 0:
		switch (obj2->GetColliderType())
		{
		case 0:
			return (obj1->min.x <= obj2->max.x && obj1->max.x >= obj2->max.x) &&
				(obj1->min.y <= obj2->max.y && obj1->max.y >= obj2->max.y) &&
				(obj1->min.z <= obj2->max.z && obj1->max.z >= obj2->max.z);
			break;

		case 1:
			sphere = obj2->GetPosition();
			x = fmaxf(obj1->min.x, fminf(sphere.x, obj1->max.x));
			y = fmaxf(obj1->min.y, fminf(sphere.y, obj1->max.y));
			z = fmaxf(obj1->min.z, fminf(sphere.z, obj1->max.z));

			dist = sqrt((x - sphere.x) * (x - sphere.x) +
				(y - sphere.y) * (y - sphere.y) +
				(z - sphere.z) * (x - sphere.z)
			);

			return dist < obj2->GetSphereRadius();
			break;
		}
		break;

	case 1:
		switch (obj2->GetColliderType())
		{
		case 0:
			sphere = obj1->GetPosition();
			x = fmaxf(obj2->min.x, fminf(sphere.x, obj2->max.x));
			y = fmaxf(obj2->min.y, fminf(sphere.y, obj2->max.y));
			z = fmaxf(obj2->min.z, fminf(sphere.z, obj2->max.z));

			dist = sqrt((x - sphere.x) * (x - sphere.x) +
				(y - sphere.y) * (y - sphere.y) +
				(z - sphere.z) * (x - sphere.z)
			);

			return dist < obj1->GetSphereRadius();
			break;

		case 1:
			glm::vec3 a = obj1->GetPosition();
			glm::vec3 b = obj2->GetPosition();

			dist = sqrt((a.x - b.x) * (a.x - b.x) +
				(a.y - b.y) * (a.y - b.y) +
				(a.z - b.z) * (a.z - b.z)
			);

			return dist < (obj1->GetSphereRadius() + obj2->GetSphereRadius());
			break;

		}
		break;
	}
	return false;
}

bool KinematicController::SpherePlaneCollision(Object* Sphere, Object* AABB)
{
	glm::vec3 ray = glm::normalize(Sphere->GetRigidbody()->GetVelocity());
	//ray = Sphere->GetRigidbody()->GetVelocity();
	std::vector<Plane*>& planes = AABB->GetPlanes();

	glm::vec3 IntersectPoint;
	int planeNo = 0;

	bool intersected = false;
	float pointDist;
	glm::vec3 TempIntersectPoint;

	for (int i = 0; i < planes.size(); i++)
	{
		if (planes[i]->CheckIntersection(ray, Sphere->GetPosition(), TempIntersectPoint))
		{
			if (!intersected)
			{
				intersected = true;
				IntersectPoint = TempIntersectPoint;
				planeNo = i;
				pointDist = (TempIntersectPoint.x - Sphere->GetPosition().x) * (TempIntersectPoint.x - Sphere->GetPosition().x) +
					(TempIntersectPoint.y - Sphere->GetPosition().y) * (TempIntersectPoint.y - Sphere->GetPosition().y) +
					(TempIntersectPoint.z - Sphere->GetPosition().z) * (TempIntersectPoint.z - Sphere->GetPosition().z);
			}
			else
			{
				float newPointDist = (TempIntersectPoint.x - Sphere->GetPosition().x) * (TempIntersectPoint.x - Sphere->GetPosition().x) +
					(TempIntersectPoint.y - Sphere->GetPosition().y) * (TempIntersectPoint.y - Sphere->GetPosition().y) +
					(TempIntersectPoint.z - Sphere->GetPosition().z) * (TempIntersectPoint.z - Sphere->GetPosition().z);

				if (newPointDist < pointDist)
				{
					IntersectPoint = TempIntersectPoint;
					planeNo = i;
					pointDist = newPointDist;
				}
			}
		}
	}

	glm::vec3 desiredPos, actualPos;
	actualPos = Sphere->GetPosition();
	desiredPos = IntersectPoint + (-ray*Sphere->GetSphereRadius());

	float Mag = glm::dot(Sphere->GetRigidbody()->GetVelocity(), -planes[planeNo]->normal);
	Sphere->GetRigidbody()->AddForce(planes[planeNo]->normal * Mag * 2.0f, VelocityChange);
	Sphere->SetPosition(desiredPos);
	return true;
}

bool KinematicController::SphereSphereCollision(Object* obj1, Object* obj2)
{
	glm::vec3 CollisionPoint;
	glm::vec3 CPVector;

	float mass1 = obj1->GetRigidbody()->GetMass();
	float mass2 = obj2->GetRigidbody()->GetMass();

	CPVector = glm::normalize(obj1->GetPosition() - obj2->GetPosition());
	CollisionPoint = obj1->GetSphereRadius() * CPVector;

	float Mag1 = glm::dot(obj1->GetRigidbody()->GetMomentum(), CPVector);
	float Mag2 = glm::dot(obj2->GetRigidbody()->GetMomentum(), CPVector);


	if (!obj1->GetRigidbody()->getKinematic() && !obj2->GetRigidbody()->getKinematic())
	{
		glm::vec3 TotalMomentum = (Mag1 * CPVector) + (Mag2 * CPVector);
		glm::vec3 velAfterCol = TotalMomentum / (mass1 + mass2);
		//obj1->GetRigidbody()->AddVelocity(velAfterCol);
		//obj2->GetRigidbody()->AddVelocity(velAfterCol);
		obj1->GetRigidbody()->AddForce(-velAfterCol, VelocityChange);
		obj2->GetRigidbody()->AddForce(-velAfterCol, VelocityChange);
	}
	else if (!obj1->GetRigidbody()->getKinematic())
	{
		glm::vec3 velAfterCol = (Mag1 * CPVector) / mass1;
		//obj1->GetRigidbody()->AddVelocity(-velAfterCol);
		obj1->GetRigidbody()->AddForce(-velAfterCol, VelocityChange);
	}
	else
	{
		glm::vec3 velAfterCol = (Mag2 * CPVector) / mass2;
		//obj2->GetRigidbody()->AddVelocity(-velAfterCol);
		obj2->GetRigidbody()->AddForce(-velAfterCol, VelocityChange);
	}
	
	return true;
}

void KinematicController::CheckPreciseCollision(Object* obj1, Object* obj2)
{
	if (!obj1->GetRigidbody()->getKinematic() && !obj2->GetRigidbody()->getKinematic())
	{
		switch (obj1->GetColliderType())
		{
		case 0:
			switch (obj2->GetColliderType())
			{
			case 0:
				break;
			case 1:
				//SpherePlaneCollision(obj2, obj1);
				break;
			}
			break;
		case 1:
			switch (obj2->GetColliderType())
			{
			case 0:
				//SpherePlaneCollision(obj1, obj2);
				break;
			case 1:
				SphereSphereCollision(obj1, obj2);
				break;
			}
			break;
		}
	}
	else
	{
		switch (obj1->GetColliderType())
		{
		case 0:
			switch (obj2->GetColliderType())
			{
			case 0:
				break;
			case 1:
				SpherePlaneCollision(obj2, obj1);
				break;
			}
			break;
		case 1:
			switch (obj2->GetColliderType())
			{
			case 0:
				SpherePlaneCollision(obj1, obj2);
				break;
			case 1:
				//SphereSphereCollision(obj1, obj2);
				break;
			}
			break;
		}
	}
}

void KinematicController::Update(std::vector<Object*>& objs)
{
	//std::cout << "Updating Collision Detection";
	CheckGeneralCollisions(objs);
}