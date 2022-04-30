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

	objectModel.textureId = GenTexture(_texturePath);

	projectionLoc = glGetUniformLocation(shad.getProgId(), "u_Projection");
	modelLoc = glGetUniformLocation(shad.getProgId(), "u_Model");
	viewLoc = glGetUniformLocation(shad.getProgId(), "u_View");
	lightLoc = glGetUniformLocation(shad.getProgId(), "u_Light");

	
}

Object::Object(const std::string& _modelPath, const std::string& _texturePath, Shader shad, glm::vec3 pos, glm::vec3 rot) : Rigidbody(this)
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

	objectModel.textureId = GenTexture(_texturePath);

	projectionLoc = glGetUniformLocation(shad.getProgId(), "u_Projection");
	modelLoc = glGetUniformLocation(shad.getProgId(), "u_Model");
	viewLoc = glGetUniformLocation(shad.getProgId(), "u_View");
	lightLoc = glGetUniformLocation(shad.getProgId(), "u_Light");

	
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

	objectModel.textureId = GenTexture(_texturePath);

	projectionLoc = glGetUniformLocation(shad.getProgId(), "u_Projection");
	modelLoc = glGetUniformLocation(shad.getProgId(), "u_Model");
	viewLoc = glGetUniformLocation(shad.getProgId(), "u_View");
	lightLoc = glGetUniformLocation(shad.getProgId(), "u_Light");
	lightColLoc = glGetUniformLocation(shad.getProgId(), "u_LightColor");

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

	objectModel.textureId = GenTexture(_texturePath);

	projectionLoc = glGetUniformLocation(shad.getProgId(), "u_Projection");
	modelLoc = glGetUniformLocation(shad.getProgId(), "u_Model");
	viewLoc = glGetUniformLocation(shad.getProgId(), "u_View");
	lightLoc = glGetUniformLocation(shad.getProgId(), "u_Light");

	

}

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

	projectionLoc = glGetUniformLocation(shad.getProgId(), "u_Projection");
	modelLoc = glGetUniformLocation(shad.getProgId(), "u_Model");
	viewLoc = glGetUniformLocation(shad.getProgId(), "u_View");
	lightLoc = glGetUniformLocation(shad.getProgId(), "u_Light");

	
}

Object::Object(const std::string& _modelPath, Shader shad, glm::vec3 pos, glm::vec3 rot) : Rigidbody(this)
{
	if (WfModelLoad(_modelPath.c_str(), &objectModel) != 0)
	{
		throw std::runtime_error("Error loading model");
	}

	position = pos;
	rotation = rot;
	scale = glm::vec3(1.0f);

	std::cout << "Position:" << pos.x << " " << pos.y << " " << pos.z << std::endl;

	GetVertices(_modelPath);
	calculateAABB();

	projectionLoc = glGetUniformLocation(shad.getProgId(), "u_Projection");
	modelLoc = glGetUniformLocation(shad.getProgId(), "u_Model");
	viewLoc = glGetUniformLocation(shad.getProgId(), "u_View");
	lightLoc = glGetUniformLocation(shad.getProgId(), "u_Light");

	
	
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

	projectionLoc = glGetUniformLocation(shad.getProgId(), "u_Projection");
	modelLoc = glGetUniformLocation(shad.getProgId(), "u_Model");
	viewLoc = glGetUniformLocation(shad.getProgId(), "u_View");
	lightLoc = glGetUniformLocation(shad.getProgId(), "u_Light");
	lightColLoc = glGetUniformLocation(shad.getProgId(), "u_LightColor");

	
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

	projectionLoc = glGetUniformLocation(shad.getProgId(), "u_Projection");
	modelLoc = glGetUniformLocation(shad.getProgId(), "u_Model");
	viewLoc = glGetUniformLocation(shad.getProgId(), "u_View");
	lightLoc = glGetUniformLocation(shad.getProgId(), "u_Light");

	

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

	unsigned char* data = stbi_load(_texturePath.c_str(), &w, &h, NULL, 4);

	if (!data)
	{
		throw std::runtime_error("texture not loaded");
	}

	GLuint textId = 0;
	glGenTextures(1, &textId);

	if (!textId)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, textId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	free(data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textId;
}

void Object::GetVertices(const std::string& _modelPath)
{
	FILE* file;
	//file = fopen(_modelPath.c_str(), "r");
	fopen_s(&file, _modelPath.c_str(), "r");

	if (file == NULL)
	{
		throw std::runtime_error("file failed to open");
	}
	while (1)
	{
		char lineHeader[128];

		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}
	}
	fclose(file);
}

void Object::calculateAABB()
{
	GLfloat
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;
	min_x = max_x = vertices[0].x;
	min_y = max_y = vertices[0].y;
	min_z = max_z = vertices[0].z;

	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].x < min_x) min_x = vertices[i].x;
		if (vertices[i].x > max_x) max_x = vertices[i].x;
		if (vertices[i].y < min_y) min_y = vertices[i].y;
		if (vertices[i].y > max_y) max_y = vertices[i].y;
		if (vertices[i].z < min_z) min_z = vertices[i].z;
		if (vertices[i].z > max_z) max_z = vertices[i].z;
	}

	size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);
	centerOffset = glm::vec3((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
	center = glm::vec3(position.x + centerOffset.x, position.y + centerOffset.y, position.z + centerOffset.z);
	initialMin = glm::vec3(min_x, min_y, min_z);
	initialMax = glm::vec3(max_x, max_y, max_z);

	UpdateCollider();
	colliderRadius = max_y;
	//std::cout << "size:" << size.x << " " << size.y << " " << size.z << std::endl;
	//std::cout << "Min:" << min.x << " " << min.y << " " << min.z << std::endl;
	//std::cout << "Max:" << max.x << " " << max.y << " " << max.z << std::endl;

	//0
	Planes.push_back(new Plane(glm::vec3(max_x, max_y, max_z), glm::vec3(min_x, max_y, max_z), glm::vec3(min_x, max_y, min_z), position, scale, rotation));
	//1
	Planes.push_back(new Plane(glm::vec3(max_x, max_y, max_z), glm::vec3(max_x, min_y, max_z), glm::vec3(min_x, min_y, max_z), position, scale, rotation));
	//2
	Planes.push_back(new Plane(glm::vec3(min_x, max_y, max_z), glm::vec3(min_x, min_y, max_z), glm::vec3(min_x, min_y, min_z), position, scale, rotation));
	//3
	Planes.push_back(new Plane(glm::vec3(max_x, max_y, min_z), glm::vec3(min_x, max_y, min_z), glm::vec3(min_x, min_y, min_z), position, scale, rotation));
	//4
	Planes.push_back(new Plane(glm::vec3(max_x, max_y, max_z), glm::vec3(max_x, max_y, min_z), glm::vec3(max_x, min_y, min_z), position, scale, rotation));
	//5
	Planes.push_back(new Plane(glm::vec3(max_x, min_y, max_z), glm::vec3(max_x, min_y, min_z), glm::vec3(min_x, min_y, min_z), position, scale, rotation));
	
	std::cout << std::endl;
}

void Object::DrawObject(Shader& shad, SDL_Window *window, glm::vec3 lightPos, glm::vec3 lightCol, glm::mat4 cam)
{
	SDL_GetWindowSize(window, &width, &height);
	
	shad.use();
	glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)width / (float)height, 0.1f, 100.0f);

	glm::mat4 model(1.0f);

	//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
	model = glm::translate(model, position);
	model = setModelRotation(model);
	model = glm::scale(model, scale);

	glUniform3f(lightLoc, lightPos.x, lightPos.y, lightPos.z);

	glUniform3f(lightColLoc, lightCol.x, lightCol.y, lightCol.z);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cam));

	// Upload the projection matrix
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));



	glBindVertexArray(objectModel.vaoId);
	glBindTexture(GL_TEXTURE_2D, objectModel.textureId);


	glDrawArrays(GL_TRIANGLES, 0, objectModel.vertexCount);

	shad.unUse();

}

void Object::Update(float DeltaTime)
{
	for (int i = 0; i < ScriptNo; i++)
	{
		scripts[i]->Update();
	}
	for (int i = 0; i < Planes.size(); i++)
	{
		Planes[i]->UpdatePoints(position, scale, rotation);
	}
	
}

void Object::UpdatePhysics(float DeltaTime, std::vector<Object*>& objs, int address)
{
	Rigidbody.Update(DeltaTime);
	UpdateCollider();
	//std::cout << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
}

glm::mat4 Object::setModelRotation(glm::mat4 _model)
{
	_model = glm::rotate(_model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	_model = glm::rotate(_model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	_model = glm::rotate(_model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	return _model;

}

void Object::AddScript(ObjectScript* _script)
{
	scripts.push_back(_script);
	ScriptNo++;
}

void Object::StartScripts()
{
	for (int i = 0; i < ScriptNo; i++)
	{
		scripts[i]->Start();
	}
}

//object movement functions
void Object::translation(glm::vec3 movement)
{
	//std::cout << "Translating" << std::endl;
	//std::cout << "--------------------" << std::endl;
	//std::cout << position.x << " " << position.y << " " << position.z << std::endl;
	//std::cout << movement.x << " " << movement.y << " " << movement.z << std::endl;
	position += movement;
	//std::cout << position.x << " " << position.y << " " << position.z << std::endl;
	//std::cout << "***************" << std::endl;
}

void Object::rotate(glm::vec3 _rotation)
{
	//std::cout << "Rotating" << std::endl;
	//std::cout << "--------------------" << std::endl;
	//std::cout << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
	//std::cout << _rotation.x << " " << _rotation.y << " " << _rotation.z << std::endl;
	rotation += _rotation;
	//std::cout << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
	//std::cout << "***************" << std::endl;
	
}

void Object::SetPosition(glm::vec3 pos)
{
	//position = pos;
	//std::cout << "Setting Position" << std::endl;
	//std::cout << "--------------------" << std::endl;
	//std::cout << position.x << " " << position.y << " " << position.z << std::endl;
	//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
	position = pos;
	//std::cout << position.x << " " << position.y << " " << position.z << std::endl;
	//std::cout << "***************" << std::endl;
	UpdateCollider();
}

void Object::SetRotation(glm::vec3 rot)
{
	rotation = rot;
}

glm::vec3 Object::GetPosition()
{
	return position;
}

glm::vec3 Object::GetRotation()
{
	return rotation;
}

int Object::GetColliderType()
{
	return Rigidbody.GetColliderType();
}

float Object::GetSphereRadius()
{
	return colliderRadius;
}