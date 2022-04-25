#include "Mesh.h"
#include <GL/glew.h>
#include <stdexcept>

const GLfloat positions[] =
{
	-1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f
};

Mesh::Mesh(int _type)
{
	glGenBuffers(1, &m_posVBOId);
	if (!m_posVBOId)throw std::runtime_error("Failed to allocate positions VBO");
	glBindBuffer(GL_ARRAY_BUFFER, m_posVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_vaoId);

	glBindVertexArray(m_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, m_posVBOId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

int Mesh::vert_count()
{
	return 6;
}

GLuint Mesh::id()
{
	return m_vaoId;
}