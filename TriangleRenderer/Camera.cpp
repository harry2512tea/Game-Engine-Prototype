#include "Camera.h"

Camera::Camera(glm::vec3 _Position, glm::vec3 _Rotation)
{
	Position = _Position;
	Rotation = CheckRotation(-_Rotation);
	DoRotation(Rotation);
}

glm::mat4 Camera::CreateViewMatrix()
{
	glm::mat4 ViewMat;
	ViewMat = glm::mat4_cast(RotationQuat);
	ViewMat = glm::translate(ViewMat, -Position);
	return ViewMat;
}

void Camera::SetRotation(glm::vec3 _Rotation)
{
	Rotation = CheckRotation(-_Rotation);
	RotationQuat = glm::quat();
	DoRotation(-_Rotation);
}

void Camera::Rotate(glm::vec3 _Rotation)
{
	Rotation += CheckRotation(-_Rotation);
	DoRotation(-_Rotation);
}

glm::vec3 Camera::CheckRotation(glm::vec3 _rotation)
{
	glm::vec3 newRot = _rotation;
	if (_rotation.x > 360)
	{
		_rotation.x -= 360;
	}
	else if (_rotation.x < -360)
	{
		_rotation.x += 360;
	}
	if (_rotation.y > 360)
	{
		_rotation.y -= 360;
	}
	else if (_rotation.y < -360)
	{
		_rotation.y += 360;
	}
	if (_rotation.z > 360)
	{
		_rotation.z -= 360;
	}
	else if (_rotation.z < -360)
	{
		_rotation.z += 360;
	}

	return _rotation;
}

glm::quat Camera::DoRotation(glm::vec3 Euler)
{
	glm::vec3 angles = glm::radians(CheckRotation(Euler));

	RotationQuat = glm::angleAxis(angles.x, glm::vec3(1.0f, 0.0f, 0.0f)) * RotationQuat;
	RotationQuat = glm::angleAxis(angles.y, glm::vec3(0.0f, 1.0f, 0.0f)) * RotationQuat;
	RotationQuat = glm::angleAxis(angles.z, glm::vec3(0.0f, 0.0f, 1.0f)) * RotationQuat;

	return RotationQuat;
}