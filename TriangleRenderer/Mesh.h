#pragma once
#include <GL/glew.h>

struct Mesh
{
	Mesh(int _type);

	int vert_count();

	GLuint id();

private:
	GLuint m_vaoId;
	GLuint m_posVBOId;
};