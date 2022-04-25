#include "RenderTexture.h"
#include <stdexcept>


	RenderTexture::RenderTexture(int _width, int _height)
	{
		glGenFramebuffers(1, &m_fboId);
		if (!m_fboId) throw std::runtime_error("Texture FBO error");
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_2D, m_texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		

		glGenRenderbuffers(1, &m_rboId);

		if (!m_rboId) throw std::runtime_error("Texture RBO error");

		glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texId, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboId);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	RenderTexture::~RenderTexture()
	{
		glDeleteFramebuffers;
		glDeleteTextures;
		glDeleteRenderbuffers;
	}

	void RenderTexture::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
	}
	void RenderTexture::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	GLuint RenderTexture::getTexture() const
	{
		return m_texId;
	}