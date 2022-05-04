#include "ObjectController.h"
#include "Plane.h"
#include <vector>
#include <iostream>

ObjectController* ObjectController::instance = nullptr;

//function to ensure only one instance of this class exists at any time
ObjectController* ObjectController::getInstance()
{
	//checks if the class is instantiated
	if (!instance)
	{
		//instantiates the class under the variable name instance
		instance = new ObjectController();
	}

	//returns the static instance of the class
	return instance;
}

void ObjectController::CheckGeneralCollisions(std::vector<Object*>& objs)
{
	//running through every object in the scene
	for (int i = 0; i < objs.size(); i++)
	{
		for (int O = i + 1; O < objs.size(); O++)
		{
			//checks if at least one of the objects is dynamic
			if (!objs[i]->GetRigidbody()->getKinematic() || !objs[O]->GetRigidbody()->getKinematic())
			{
				//checking if the two objects are colliding
				if (checkCollision(objs[i], objs[O]))
				{
					//std::cout << "Collision " << i << " " << O << std::endl;
					//running collision response
					CheckCollisionResponse(objs[i], objs[O]);
				}
			}
		}
	}
}

bool ObjectController::checkCollision(Object* obj1, Object* obj2)
{
	// 0 = OBB
	// 1 = Sphere
	float x, y, z, dist;
	glm::vec3 sphere;
	//used to determing whether or not two objects collide
	switch (obj1->GetColliderType())
	{
	case 0:
		switch (obj2->GetColliderType())
		{
		case 0:
			//checks if the upper and lower bounds of two axis aligned bounding boxes overlap
			//and returns the value
			return (obj1->min.x <= obj2->max.x && obj1->max.x >= obj2->max.x) &&
				(obj1->min.y <= obj2->max.y && obj1->max.y >= obj2->max.y) &&
				(obj1->min.z <= obj2->max.z && obj1->max.z >= obj2->max.z);
			break;

		case 1:
			sphere = obj2->GetPosition();
			//gets the closest point between the sphere and the bounding box
			x = fmaxf(obj1->min.x, fminf(sphere.x, obj1->max.x));
			y = fmaxf(obj1->min.y, fminf(sphere.y, obj1->max.y));
			z = fmaxf(obj1->min.z, fminf(sphere.z, obj1->max.z));

			//finds the distance between the sphere and the bounding box
			dist = sqrt(
				(x - sphere.x) * (x - sphere.x) +
				(y - sphere.y) * (y - sphere.y) +
				(z - sphere.z) * (z - sphere.z)
			);

			//checks if the sphere is overlapping with the bounding box
			return dist < obj2->GetSphereRadius();
			break;
		}
		break;

	case 1:
		switch (obj2->GetColliderType())
		{
		case 0:
			sphere = obj1->GetPosition();
			//gets the closest point between the sphere and the bounding box
			x = fmaxf(obj2->min.x, fminf(sphere.x, obj2->max.x));
			y = fmaxf(obj2->min.y, fminf(sphere.y, obj2->max.y));
			z = fmaxf(obj2->min.z, fminf(sphere.z, obj2->max.z));

			//finds the distance between the sphere and the bounding box
			dist = sqrt(
				(x - sphere.x) * (x - sphere.x) +
				(y - sphere.y) * (y - sphere.y) +
				(z - sphere.z) * (z - sphere.z)
			);
			//checks if the sphere is overlapping with the bounding box
			return dist < obj1->GetSphereRadius();
			break;

		case 1:
			//storing the position of the two sphere in variables.
			glm::vec3 a = obj1->GetPosition();
			glm::vec3 b = obj2->GetPosition();

			//calculates the difference between the two spheres
			dist = glm::distance(a, b);

			//calculates the minimum separation between the two spheres that would result in a collision
			float collisionDist = obj1->GetSphereRadius() + obj2->GetSphereRadius();

			//checks if the distance between the two spheres is less than the minimum separation
			return dist <= collisionDist;
			break;

		}
		break;
	}
	return false;
}

bool ObjectController::SpherePlaneCollision(Object* Sphere, Object* OBB)
{
	glm::vec3 ray = glm::normalize(Sphere->GetRigidbody()->GetVelocity());

	//retrieving the planes of the bounding box and storing them within the function
	std::vector<OBBPlane*>& planes = OBB->GetPlanes();

	//settting up the variables used for calculations
	glm::vec3 IntersectPoint;
	int planeNo = -1;

	bool intersected = false;
	float pointDist;
	glm::vec3 TempIntersectPoint;

	//running a collision check between the sphere and all the planes of the bounding box
	for (int i = 0; i < planes.size(); i++)
	{
		//uses the plane class' built in intersection function to test for a collision
		if (planes[i]->CheckIntersection(-planes[i]->normal, Sphere->GetPosition(), TempIntersectPoint))
		{
			//sets the values for the first possible intersection
			if (!intersected)
			{
				glm::vec3 direction = glm::normalize(TempIntersectPoint - Sphere->GetPosition());
				direction = glm::vec3(round(direction.x * 10000) / 10000, round(direction.y * 10000) / 10000, round(direction.z * 10000) / 10000);
				glm::vec3 tempNorm = planes[i]->normal;
				tempNorm = glm::vec3(round(tempNorm.x * 10000) / 10000, round(tempNorm.y * 10000) / 10000, round(tempNorm.z * 10000) / 10000);
				if (direction != tempNorm)
				{
					intersected = true;
					IntersectPoint = TempIntersectPoint;
					planeNo = i;
					pointDist = (TempIntersectPoint.x - Sphere->GetPosition().x) * (TempIntersectPoint.x - Sphere->GetPosition().x) +
						(TempIntersectPoint.y - Sphere->GetPosition().y) * (TempIntersectPoint.y - Sphere->GetPosition().y) +
						(TempIntersectPoint.z - Sphere->GetPosition().z) * (TempIntersectPoint.z - Sphere->GetPosition().z);
				}
			}
			//runs through the rest of the planes to check if there is a closer collision point
			else
			{
				glm::vec3 direction = glm::normalize(TempIntersectPoint - Sphere->GetPosition());
				direction = glm::vec3(round(direction.x * 10000) / 10000, round(direction.y * 10000) / 10000, round(direction.z * 10000) / 10000);
				glm::vec3 tempNorm = planes[i]->normal;
				tempNorm = glm::vec3(round(tempNorm.x * 10000) / 10000, round(tempNorm.y * 10000) / 10000, round(tempNorm.z * 10000) / 10000);

				if (direction != tempNorm)
				{
					//calculates the distance between the collision point and the sphere
					float newPointDist = (TempIntersectPoint.x - Sphere->GetPosition().x) * (TempIntersectPoint.x - Sphere->GetPosition().x) +
						(TempIntersectPoint.y - Sphere->GetPosition().y) * (TempIntersectPoint.y - Sphere->GetPosition().y) +
						(TempIntersectPoint.z - Sphere->GetPosition().z) * (TempIntersectPoint.z - Sphere->GetPosition().z);

					//sets a new collision point if the new distance
					//is less than the distance from the original collision point
					if (newPointDist < pointDist)
					{
						IntersectPoint = TempIntersectPoint;
						planeNo = i;
						pointDist = newPointDist;
					}
				}
			}
		}
	}

	
	//determining where the sphere should be positioned to prevent clipping
	glm::vec3 desiredPos, actualPos;
	actualPos = Sphere->GetPosition();
	//checks if there was a collision
	if (planeNo > -1)
	{
		std::cout << planeNo << std::endl;
		glm::vec3 velocity = Sphere->GetRigidbody()->GetVelocity();
		if (planeNo != 0)
		{

			std::cout << "stop pls" << std::endl;
		}


		

		//updates the collision point to the shortest distance between the sphere and plane using the plane's normal
		bool collide = planes[planeNo]->getIntersection(-planes[planeNo]->normal, Sphere->GetPosition(), IntersectPoint, Sphere->GetSphereRadius());
		float Dist = (IntersectPoint.x - Sphere->GetPosition().x) * (IntersectPoint.x - Sphere->GetPosition().x) +
			(IntersectPoint.y - Sphere->GetPosition().y) * (IntersectPoint.y - Sphere->GetPosition().y) +
			(IntersectPoint.z - Sphere->GetPosition().z) * (IntersectPoint.z - Sphere->GetPosition().z);
		if (Dist < Sphere->GetSphereRadius() * Sphere->GetSphereRadius())
		{
			float Mag = glm::dot(velocity, planes[planeNo]->normal);
			if (Mag < 0 && collide)
			{
				//*******************************************************collision point calculations***************************************************

				//calculates the position the sphere should be when colliding by multiplying 
				//the normal of the plane by the radius of the sphere, and adding that to the collision point
				desiredPos = IntersectPoint + (planes[planeNo]->normal * Sphere->GetSphereRadius() * 1.0f);

				

				//*******************************************************angular velocity to linear velocity calculations***************************************************


				glm::mat3 InertiaTensorBody = Sphere->GetRigidbody()->GetInertiaTensor();

				glm::mat3 rotationMatrix = glm::mat3(Sphere->GetRotation());

				glm::mat3 InverseInertiaTensor = rotationMatrix * glm::inverse(InertiaTensorBody) * glm::transpose(rotationMatrix);

				glm::vec3 torque;
				glm::vec3 angular_momentum;
				glm::vec3 angular_velocity;
				glm::vec3 momentum = Sphere->GetRigidbody()->GetMomentum();

				Mag = glm::dot(momentum, -planes[planeNo]->normal);
				glm::vec3 momentumInParallel = momentum - (Mag * -planes[planeNo]->normal);

				Mag = glm::dot(momentum, -planes[planeNo]->normal);
				glm::vec3 momentumInDirection = Mag * -planes[planeNo]->normal;

				float momentumScalar = sqrt((momentumInDirection.x * momentumInDirection.x) + (momentumInDirection.y * momentumInDirection.y) + (momentumInDirection.z * momentumInDirection.z));

				float frictionForce = (momentumScalar*2) * Sphere->GetRigidbody()->GetFriction();

				glm::vec3 friction = -glm::normalize(momentumInParallel) * frictionForce;

				glm::vec3 changeInMomentum = (momentumInParallel - friction);

				torque = changeInMomentum * Sphere->GetSphereRadius() + (-momentumInDirection - momentumInDirection);

				Sphere->GetRigidbody()->AddTorque(torque);

				Sphere->GetRigidbody()->AddForce(-glm::normalize(momentumInParallel) * frictionForce, Impulse);





				//calculating the magnitude of the velocity in the direction of the plane
				Mag = glm::dot(velocity, -planes[planeNo]->normal);

				//retrieving the angular velocity of the ball
				glm::vec3 angVel = Sphere->GetRigidbody()->GetRotVel();

				//converting the angular velocity to linear velocity at the edge of the sphere
				glm::vec3 linVel = angVel * Sphere->GetSphereRadius();

				//calculating the angle between the origin, and the plane's normal
				float angle = glm::angle(glm::vec3(0, 1, 0), planes[planeNo]->normal);

				//creates a quaternion to rotate the linear velocity to the point of collision
				glm::quat rotat = glm::angleAxis(angle, glm::cross(planes[planeNo]->normal, glm::vec3(0, 1, 0)));

				//rotates the linear velocity vector to the correct orientation of the collision point.
				linVel = linVel * glm::angleAxis(glm::radians(-90.0f), planes[planeNo]->normal);
				linVel = rotat * linVel;

				//removing any negligable amounts that could impact calculations
				if (abs(linVel.x) < 0.0001f) linVel.x = 0;
				if (abs(linVel.y) < 0.0001f) linVel.y = 0;
				if (abs(linVel.z) < 0.0001f) linVel.z = 0;

				//calculating the velocity component not in the direction of the plane
				glm::vec3 velInDir = velocity - (Mag * -planes[planeNo]->normal);

				//calculating the change in velocity due to angular momentum.
				glm::vec3 newVel = linVel - velInDir;

				//applying that change in velocity
				//Sphere->GetRigidbody()->AddForce(newVel * (Sphere->GetRigidbody()->GetElasticity() * 0.3f), VelocityChange);

				//*******************************************************bounciness calculations***************************************************

				//calculating the velocity change of an elastic collision between the sphere and the plane
				glm::vec3 force = planes[planeNo]->normal * Mag * 2.0f;

				//applies the velocity change of an inelastic collision between the sphere and the plane, using the elastic collision value
				Sphere->GetRigidbody()->AddForce(force * Sphere->GetRigidbody()->GetElasticity(), VelocityChange);

				//setting the sphere's position to the actual collision position
				Sphere->SetPosition(desiredPos);

				//*******************************************************friction calculations***************************************************

				//retrieving the new velocity
				velocity = Sphere->GetRigidbody()->GetVelocity();
				glm::vec3 frictionVelocity = velocity * (1 - Sphere->GetRigidbody()->GetFriction() - velocity);
				//taking friction into account with collisions
				//Sphere->GetRigidbody()->AddForce(frictionVelocity, VelocityChange);

				//*******************************************************rotational velocity calculations***************************************************

				//recalculating the new rotational velocity of the sphere
				glm::vec3 rotVel = glm::cross(planes[planeNo]->normal * Sphere->GetSphereRadius(), -Sphere->GetRigidbody()->GetVelocity());

				//applying the new rotational velocity
				Sphere->GetRigidbody()->SetRotationalVel(rotVel);


				return true;
			}
		}
		
	}
	return false;
}

bool ObjectController::SphereSphereCollision(Object* obj1, Object* obj2)
{
	glm::vec3 CollisionPoint;
	glm::vec3 CPVector;

	float mass1 = obj1->GetRigidbody()->GetMass();
	float mass2 = obj2->GetRigidbody()->GetMass();

	glm::vec3 vel1 = obj1->GetRigidbody()->GetVelocity();
	glm::vec3 vel2 = obj2->GetRigidbody()->GetVelocity();

	if (!obj1->GetRigidbody()->getKinematic() && !obj2->GetRigidbody()->getKinematic())
	{
		CPVector = glm::normalize(obj1->GetPosition() - obj2->GetPosition());
		CollisionPoint = (obj1->GetSphereRadius() * -CPVector) + obj1->GetPosition();

		float Mag1 = glm::dot(obj1->GetRigidbody()->GetVelocity(), CPVector);
		float Mag2 = glm::dot(obj2->GetRigidbody()->GetVelocity(), CPVector);


		obj2->GetRigidbody()->AddForce((Mag1 * CPVector) - (Mag2 * CPVector) * 1.0f * obj1->GetRigidbody()->GetElasticity(), VelocityChange);
		obj1->GetRigidbody()->AddForce((Mag2 * CPVector) - (Mag1 * CPVector) * 1.0f * obj2->GetRigidbody()->GetElasticity(), VelocityChange);

		glm::vec3 actualPoint = obj2->GetPosition();
		glm::vec3 desiredPoint = (-CPVector * obj2->GetSphereRadius()) + CollisionPoint;
		obj2->SetPosition(desiredPoint);


		//glm::vec3 TotalMomentum = ((Mag1 * CPVector) * mass1) + ((Mag2 * CPVector) * mass2);
		//glm::vec3 TotalVelocity = TotalMomentum / (mass1 + mass2);

	}
	else if (!obj1->GetRigidbody()->getKinematic())
	{
		CPVector = glm::normalize(obj1->GetPosition() - obj2->GetPosition());
		CollisionPoint = (obj2->GetSphereRadius() * CPVector) + obj2->GetPosition();

		float Mag = glm::dot(obj1->GetRigidbody()->GetVelocity(), -CPVector);
		obj1->GetRigidbody()->AddForce((Mag * CPVector) * 2.0f * obj1->GetRigidbody()->GetElasticity(), VelocityChange);

		glm::vec3 actualPoint = obj1->GetPosition();
		glm::vec3 desiredPoint = (CPVector * obj1->GetSphereRadius()) + CollisionPoint;
		obj1->SetPosition(desiredPoint);
	}
	else
	{
		CPVector = glm::normalize(obj2->GetPosition() - obj1->GetPosition());
		CollisionPoint = (obj1->GetSphereRadius() * CPVector) + obj2->GetPosition();

		float Mag = glm::dot(obj2->GetRigidbody()->GetVelocity(), -CPVector);
		obj2->GetRigidbody()->AddForce((Mag * CPVector) * 2.0f * obj2->GetRigidbody()->GetElasticity(), VelocityChange);

		glm::vec3 actualPoint = obj2->GetPosition();
		glm::vec3 desiredPoint = (CPVector * obj2->GetSphereRadius()) + CollisionPoint;
		obj1->SetPosition(desiredPoint);
	}
	
	return true;
}

void ObjectController::CheckCollisionResponse(Object* obj1, Object* obj2)
{
	//series of if statements and switches to determine which collision detection algorithm to use

	//determins whether the objects are dynamic or not, and which collision algorithms to use.
	// 0 = OBB
	// 1 = Sphere
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
				//runs if both of the collider types are spheres, and both objects are dynamic
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
				//only runs if there is a box collider, and a sphere collider with only one dynamic object
				SpherePlaneCollision(obj2, obj1);
				break;
			}
			break;
		case 1:
			switch (obj2->GetColliderType())
			{
			case 0:
				//only runs if there is a box collider, and a sphere collider with only one dynamic object
				SpherePlaneCollision(obj1, obj2);
				break;
			case 1:
				//runs if both of the collider types are spheres, and one of the objects is dynamic
				SphereSphereCollision(obj1, obj2);
				break;
			}
			break;
		}
	}
}

//called every frame
void ObjectController::Update(std::vector<Object*>& objs, float deltaTime)
{
	DeltaTime = deltaTime;
	//check for collisions between all the objects in the scene
	CheckGeneralCollisions(objs);
}