#pragma warning(disable : 4996)
#include "Object.h"

#include <GL/glew.h>
#include <stdexcept>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

Object::Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad, glm::vec3 pos, glm::vec3 rot, glm::vec3 _scale) : Rigidbody(this)
{
	if (WfModelLoad(_modelPath.c_str(), &objectModel) != 0)
	{
		throw std::runtime_error("Error loading model");
	}

	position = pos;
	rotation = rot;
	scale = _scale;

	GetVertices(_modelPath);
	calculateAABB();
	calculateOBB();

	objectModel.textureId = GenTexture(_texturePath);

	GetUniforms(shad);
	
}

/*Object::Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad, glm::vec3 pos, glm::vec3 rot) : Rigidbody(this)
{
	if (WfModelLoad(_modelPath.c_str(), &objectModel) != 0)
	{
		throw std::runtime_error("Error loading model");
	}

	position = pos;
	rotation = rot;
	scale = glm::vec3(1.0f);

	GetVertices(_modelPath);
	calculateAABB();
	calculateOBB();

	objectModel.textureId = GenTexture(_texturePath);

	GetUniforms(shad);
	
}

Object::Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad, glm::vec3 pos) : Rigidbody(this)
{
	if (WfModelLoad(_modelPath.c_str(), &objectModel) != 0)
	{
		throw std::runtime_error("Error loading model");
	}

	position = pos;
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);

	GetVertices(_modelPath);
	calculateAABB();
	calculateOBB();

	objectModel.textureId = GenTexture(_texturePath);

	GetUniforms(shad);

}

Object::Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad) : Rigidbody(this)
{
	if (WfModelLoad(_modelPath.c_str(), &objectModel) != 0)
	{
		throw std::runtime_error("Error loading model");
	}

	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);

	GetVertices(_modelPath);
	calculateAABB();
	calculateOBB();

	objectModel.textureId = GenTexture(_texturePath);

	GetUniforms(shad);
	

}*/

Object::Object(const std::string& _modelPath, Shader shad, glm::vec3 pos, glm::vec3 rot, glm::vec3 _scale) : Rigidbody(this)
{
	if (WfModelLoad(_modelPath.c_str(), &objectModel) != 0)
	{
		throw std::runtime_error("Error loading model");
	}

	position = pos;
	rotation = rot;
	scale = _scale;

	GetVertices(_modelPath);
	calculateAABB();
	calculateOBB();

	GetUniforms(shad);
	
}

/*Object::Object(const std::string& _modelPath, Shader shad, glm::vec3 pos, glm::vec3 rot) : Rigidbody(this)
{
	if (WfModelLoad(_modelPath.c_str(), &objectModel) != 0)
	{
		throw std::runtime_error("Error loading model");
	}

	position = pos;
	rotation = rot;
	scale = glm::vec3(1.0f);

	//std::cout << "Position:" << pos.x << " " << pos.y << " " << pos.z << std::endl;

	GetVertices(_modelPath);
	calculateAABB();
	calculateOBB();

	GetUniforms(shad);
	
	
}

Object::Object(const std::string& _modelPath, Shader shad, glm::vec3 pos) : Rigidbody(this)
{
	if (WfModelLoad(_modelPath.c_str(), &objectModel) != 0)
	{
		throw std::runtime_error("Error loading model");
	}

	position = pos;
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);

	GetVertices(_modelPath);
	calculateAABB();
	calculateOBB();

	GetUniforms(shad);
	
}

Object::Object(const std::string& _modelPath, Shader shad) : Rigidbody(this)
{
	if (WfModelLoad(_modelPath.c_str(), &objectModel) != 0)
	{
		throw std::runtime_error("Error loading model");
	}

	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);

	GetVertices(_modelPath);
	calculateAABB();
	calculateOBB();

	GetUniforms(shad);

	

}*/

void Object::GetUniforms(Shader shad)
{
	projectionLoc = glGetUniformLocation(shad.getProgId(), "u_Projection");
	modelLoc = glGetUniformLocation(shad.getProgId(), "u_Model");
	viewLoc = glGetUniformLocation(shad.getProgId(), "u_View");
	lightLoc = glGetUniformLocation(shad.getProgId(), "u_Light");
	lightColLoc = glGetUniformLocation(shad.getProgId(), "u_LightColor");
	viewPosLoc = glGetUniformLocation(shad.getProgId(), "viewPos");
}

Object::~Object()
{
	/*for (size_t i = 0; i < scripts.size(); i++)
	{
		delete scripts[i];
	}*/
}

GLuint Object::GenTexture(const std::string& _texturePath)
{
	int w = 0;
	int h = 0;

	//loading the texture file and returning the width and height.
	unsigned char* data = stbi_load(_texturePath.c_str(), &w, &h, NULL, 4);

	//checking the file loaded correctly
	if (!data)
	{
		throw std::runtime_error("texture not loaded");
	}

	//generating the texture and setting the ID
	GLuint textId = 0;
	glGenTextures(1, &textId);

	//checking the texture initialised correctly
	if (!textId)
	{
		throw std::exception();
	}

	//binding the texture to the current object
	glBindTexture(GL_TEXTURE_2D, textId);

	//attaching the texture image to the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	//clearing the texture image as its no longer needed
	free(data);

	//creating a mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//unbinding the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//returning the texture ID
	return textId;
}

void Object::GetVertices(const std::string& _modelPath)
{
	//opening the object file
	FILE* file;
	fopen_s(&file, _modelPath.c_str(), "r");

	//checking that the file opened correctly
	if (file == NULL)
	{
		throw std::runtime_error("file failed to open");
	}

	//running through until told otherwise
	while (1)
	{
		//checking the header of each line
		char lineHeader[128];

		//checking to see if its at the end of the file
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}

		//checking if the current line is a vertex
		if (strcmp(lineHeader, "v") == 0)
		{
			//getting the vertex data, and appending it to a list of vertices
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}
	}
	//closing the file
	fclose(file);
}

void Object::calculateAABB()
{
	GLfloat
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;
	//setting the initial min and max values to the first vertex
	min_x = max_x = vertices[0].x;
	min_y = max_y = vertices[0].y;
	min_z = max_z = vertices[0].z;

	for (size_t i = 0; i < vertices.size(); i++)
	{
		//checking each vertex against the max and min
		//if it exceeds either end, it becomes the new max/min
		if (vertices[i].x < min_x) min_x = vertices[i].x;
		if (vertices[i].x > max_x) max_x = vertices[i].x;
		if (vertices[i].y < min_y) min_y = vertices[i].y;
		if (vertices[i].y > max_y) max_y = vertices[i].y;
		if (vertices[i].z < min_z) min_z = vertices[i].z;
		if (vertices[i].z > max_z) max_z = vertices[i].z;
	}

	//calculating the overall size of the object
	size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);

	//calculating the center point of the bounding box
	colliderOffset = size / 2.0f;

	//setting the center to the position of the object
	//center = glm::vec3(position.x + centerOffset.x, position.y + centerOffset.y, position.z + centerOffset.z);

	//setting the initial min and max co-ordinates of the bounding box
	initialMin = glm::vec3(min_x, min_y, min_z);
	initialMax = glm::vec3(max_x, max_y, max_z);

	//setting up the collider 
	UpdateCollider();

	//using the extreme value of the bounding box as the radius for a sphere collider
	colliderRadius = fmaxf(fmaxf(max_y * scale.y, max_z * scale.z), fmax(max_x * scale.x, max_y * scale.y));

	//setting up the plane objects for the box collider
	// 
	//0
	Planes.push_back(new AABBPlane(glm::vec3(max_x, max_y, max_z), glm::vec3(min_x, max_y, max_z), glm::vec3(min_x, max_y, min_z), position, scale, rotation));
	//1
	Planes.push_back(new AABBPlane(glm::vec3(max_x, max_y, max_z), glm::vec3(max_x, min_y, max_z), glm::vec3(min_x, min_y, max_z), position, scale, rotation));
	//2
	Planes.push_back(new AABBPlane(glm::vec3(min_x, max_y, max_z), glm::vec3(min_x, min_y, max_z), glm::vec3(min_x, min_y, min_z), position, scale, rotation));
	//3
	Planes.push_back(new AABBPlane(glm::vec3(max_x, max_y, min_z), glm::vec3(min_x, max_y, min_z), glm::vec3(min_x, min_y, min_z), position, scale, rotation));
	//4
	Planes.push_back(new AABBPlane(glm::vec3(max_x, max_y, max_z), glm::vec3(max_x, max_y, min_z), glm::vec3(max_x, min_y, min_z), position, scale, rotation));
	//5
	Planes.push_back(new AABBPlane(glm::vec3(max_x, min_y, max_z), glm::vec3(max_x, min_y, min_z), glm::vec3(min_x, min_y, min_z), position, scale, rotation));
}

void Object::calculateOBB()
{
	OBBinitialMin = initialMin;
	OBBinitialMax = initialMax;
	float min_x, max_x,
		min_y, max_y,
		min_z, max_z;

	min_x = OBBinitialMin.x;
	min_y = OBBinitialMin.y;
	min_z = OBBinitialMin.z;
	max_x = OBBinitialMax.x;
	max_y = OBBinitialMax.y;
	max_z = OBBinitialMax.z;

	rotationQuat = glm::quat(glm::radians(rotation));
	//0
	OBBPlanes.push_back(new OBBPlane(glm::vec3(max_x, max_y, max_z), glm::vec3(min_x, max_y, max_z), glm::vec3(min_x, max_y, min_z), position, scale, rotationQuat));
	//1
	OBBPlanes.push_back(new OBBPlane(glm::vec3(max_x, max_y, max_z), glm::vec3(max_x, min_y, max_z), glm::vec3(min_x, min_y, max_z), position, scale, rotationQuat));
	//2
	OBBPlanes.push_back(new OBBPlane(glm::vec3(min_x, max_y, max_z), glm::vec3(min_x, min_y, max_z), glm::vec3(min_x, min_y, min_z), position, scale, rotationQuat));
	//3
	OBBPlanes.push_back(new OBBPlane(glm::vec3(max_x, max_y, min_z), glm::vec3(min_x, max_y, min_z), glm::vec3(min_x, min_y, min_z), position, scale, rotationQuat));
	//4
	OBBPlanes.push_back(new OBBPlane(glm::vec3(max_x, max_y, max_z), glm::vec3(max_x, max_y, min_z), glm::vec3(max_x, min_y, min_z), position, scale, rotationQuat));
	//5
	OBBPlanes.push_back(new OBBPlane(glm::vec3(max_x, min_y, max_z), glm::vec3(max_x, min_y, min_z), glm::vec3(min_x, min_y, min_z), position, scale, rotationQuat));
	std::cout;
}

void Object::UpdateCollider()
{
	//0 = OBB
	//1 = Sphere
	rotationQuat = glm::quat(glm::radians(rotation));

	//min = (initialMin * scale) + position;
	//max = (initialMax * scale) + position;

	if (previousPos != position ||
		previousRot != rotation)
	{
		glm::vec3 vertex = vertices[0] * scale * rotationQuat;

		GLfloat
			min_x, max_x,
			min_y, max_y,
			min_z, max_z;
		//setting the initial min and max values to the first vertex
		min_x = max_x = vertex.x;
		min_y = max_y = vertex.y;
		min_z = max_z = vertex.z;

		for (size_t i = 0; i < vertices.size(); i++)
		{
			vertex = (vertices[i] * scale)* rotationQuat;
			//checking each vertex against the max and min
			//if it exceeds either end, it becomes the new max/min
			if (vertex.x < min_x) min_x = vertex.x;
			if (vertex.x > max_x) max_x = vertex.x;
			if (vertex.y < min_y) min_y = vertex.y;
			if (vertex.y > max_y) max_y = vertex.y;
			if (vertex.z < min_z) min_z = vertex.z;
			if (vertex.z > max_z) max_z = vertex.z;
		}
		min = glm::vec3(min_x, min_y, min_z) + position;
		max = glm::vec3(max_x, max_y, max_z) + position;
	}

	switch (colliderType)
	{
	case 0:
		
		for (size_t i = 0; i < OBBPlanes.size(); i++)
		{
			OBBPlanes[i]->UpdatePoints(position, scale, rotationQuat);
		}
		break;
	case 1:
		colliderRadius = fmaxf(fmaxf(initialMax.y * scale.y, initialMax.z * scale.z), fmax(initialMax.x * scale.x, initialMax.y * scale.y));
		break;
	}

	previousPos = position;
	previousRot = rotation;
	previousScale = scale;
}

void Object::DrawObject(Shader& shad, SDL_Window *window, glm::vec3 lightPos, glm::vec3 lightCol, glm::mat4 cam, glm::vec3 camPos)
{
	SDL_GetWindowSize(window, &width, &height);
	
	//binding the object's shader
	shad.use();

	//calculating the projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)width / (float)height, 0.1f, 100.0f);

	//initialising the model matrix
	model = glm::mat4(1.0f);

	//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
	// 
	//performing transformations on the model matrix
	
	rotationQuat = glm::quat(glm::radians(-rotation));

	
	model = glm::translate(model, position);
	
	//model = setModelRotation(model);
	model = model * glm::mat4_cast(rotationQuat);
	model = glm::scale(model, scale);

	//setting the light position in the shader
	glUniform3f(lightLoc, lightPos.x, lightPos.y, lightPos.z);

	//setting the light colour in the shader
	glUniform3f(lightColLoc, lightCol.x, lightCol.y, lightCol.z);

	glUniform3f(viewPosLoc, camPos.x, camPos.y, camPos.z);

	//uploading the model matrix to the shader
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//uploading the camera position to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cam));

	// Upload the projection matrix to the shader
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


	//binding the object's vertex array
	glBindVertexArray(objectModel.vaoId);

	//binding the object's texture
	glBindTexture(GL_TEXTURE_2D, objectModel.textureId);

	//drawing the object
	glDrawArrays(GL_TRIANGLES, 0, objectModel.vertexCount);

	//unbinding the shader
	shad.unUse();

}

void Object::Update(float DeltaTime)
{
	//running the update function in all attached custom scripts
	for (size_t i = 0; i < scripts.size(); i++)
	{
		scripts[i]->Update();
	}

	//updating the position of the bounding box collider planes
	for (size_t i = 0; i < Planes.size(); i++)
	{
		Planes[i]->UpdatePoints(position, scale, rotation);
	}
	
}

void Object::UpdatePhysics(float DeltaTime, std::vector<Object*>& objs, int address)
{
	//running the update function on the attached rigidbody script
	Rigidbody.Update(DeltaTime);

	//updating the collider min and max
	UpdateCollider();
}

void Object::EnterCollision(Object* collision)
{
	for (size_t i = 0; i < scripts.size(); i++)
	{
		scripts[i]->OnCollisionEnter(collision);
	}
}

void Object::EnterTrigger(Object* collision)
{
	for (size_t i = 0; i < scripts.size(); i++)
	{
		scripts[i]->OnTriggerEnter(collision);
	}
}

glm::mat4 Object::setModelRotation(glm::mat4 _model)
{
	//generating a rotation matrix and multiplying the transform matrix by it
	_model = glm::rotate(_model, glm::radians(-rotation.x), glm::vec3(1, 0, 0));
	_model = glm::rotate(_model, glm::radians(-rotation.y), glm::vec3(0, 1, 0));
	_model = glm::rotate(_model, glm::radians(-rotation.z), glm::vec3(0, 0, 1));

	//returning the resulting model/transform matrix
	return _model;

}

void Object::AddScript(ObjectScript* _script)
{
	//attaching custom scripts by adding them to the list
	scripts.push_back(_script);
}

void Object::StartScripts()
{
	//running the start function on all custom scripts
	for (size_t i = 0; i < scripts.size(); i++)
	{
		scripts[i]->Start();
	}
}

//object movement functions
void Object::translation(glm::vec3 movement)
{
	//translate the object by a specified amount
	position += movement;
}

void Object::rotate(glm::vec3 _rotation)
{
	//rotating the object by a specified amount
	rotation += _rotation;
	
}

void Object::SetPosition(glm::vec3 pos)
{
	//setting the object's position
	position = pos;

	//updating the bounding box collider points
	UpdateCollider();
}

void Object::SetRotation(glm::vec3 rot)
{
	//setting the object's rotation
	rotation = rot;
}

glm::vec3 Object::GetPosition()
{
	return position;
}

glm::quat Object::GetRotation()
{
	return rotationQuat;
}

float Object::GetSphereRadius()
{
	return colliderRadius;
}