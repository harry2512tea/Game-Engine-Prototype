#include "Shader.h"

#include <fstream>

std::string load_file(const std::string& _path)
{
	std::ifstream file(_path.c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("File failed to open");
	}

	std::string rtn;
	std::string line;

	while (!file.eof())
	{
		
		std::getline(file, line);
		rtn += line + '\n';
	}

	return rtn;
}

Shader::Shader(const std::string& _vertPath, const std::string& _fragPath)
{

	//creating the vertex shader
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

	std::string contents = load_file(_vertPath);
	const char* src = contents.c_str();
	glShaderSource(vertexShaderId, 1, &src, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("Vertex Shader failed to initialise");
	}


	//creating the fragment shader
	contents = load_file(_fragPath);
	src = contents.c_str();
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &src, NULL);
	glCompileShader(fragmentShaderId);
	success = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		throw std::runtime_error("fragment shader failed to initialise");
	}

	//create the overall shader program
	m_progId = glCreateProgram();
	//attaching the vertex and fragment shaders
	glAttachShader(m_progId, vertexShaderId);
	glAttachShader(m_progId, fragmentShaderId);

	//binding the relavent attributes
	glBindAttribLocation(m_progId, 0, "a_Position");
	glBindAttribLocation(m_progId, 1, "a_TexCoord");
	glBindAttribLocation(m_progId, 2, "a_Normal");


	//linking the final program
	glLinkProgram(m_progId);
	success = 0;
	glGetProgramiv(m_progId, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("program failed to initialise");
	}


	//detatch shaders
	glDetachShader(m_progId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_progId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

}

void Shader::use()
{
	//binding the program
	glUseProgram(m_progId);
}

void Shader::unUse()
{
	//unbinding the program
	glUseProgram(0);
}

GLuint Shader::getProgId()
{
	return m_progId;
}
