#include "FBO.h"

FBO::FBO(int width, int height)
{
	generateTextures(width, height, 1, false, false);
}

FBO::FBO(int width, int height, int numColorTextures, bool depthTexture, bool stencilTexture)
{
	if (depthTexture)
		glEnable(GL_DEPTH_TEST);
	if (stencilTexture)
		glEnable(GL_STENCIL_TEST);

	generateTextures(width, height, numColorTextures, depthTexture, stencilTexture);
}

FBO::~FBO()
{
	reset();
}

void FBO::bind()
{
	//bind this FBO to OpenGL & set the viewport with the given size
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);
	glViewport(0, 0, m_width, m_height);
}

void FBO::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::generateTextures(int width, int height, unsigned int numColorTextures, bool depthTexture, bool stencilTexture)
{
	//cleaning up all textures
	reset();

	//setting the size of the textures
	m_width = width;
	m_height = height;

	// generate FBO and bind it to OpenGL
	glGenFramebuffers(1, &m_frameBufferHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferHandle);

	std::vector<GLenum> drawBuffers;
	for (int i = 0; i < numColorTextures; i++){ 
		generateColorTexture(drawBuffers, i);
	}
	// use color textures in fbo
	glDrawBuffers(numColorTextures, drawBuffers.data());

	if (depthTexture) { generateDepthTexture(); }

	if (stencilTexture) { generateStencilTexture(); }

	//check if trouble apeared while generating fbo
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ERROR: Unable to create FBO.\n");
		reset();
	}

	// unbind FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::generateColorTexture(std::vector<GLenum> &drawBuffers, unsigned int index)
{
	GLuint colorTextureHandle = createTexture();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_colorTextures.size(), GL_TEXTURE_2D, colorTextureHandle, 0);
	m_colorTextures.push_back(colorTextureHandle);
	drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + index);
}

void FBO::generateDepthTexture()
{
	m_depthTexture = createTexture();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);
}

void FBO::generateStencilTexture()
{
	m_stencilTexture = createTexture();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_stencilTexture, 0);
}

GLuint FBO::createTexture()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return textureID;
}

void FBO::resize(int width, int height)
{
	int numColorTextures = m_colorTextures.size();
	bool depthTexture = false;
	if (m_depthTexture != INVALID_OGL_VALUE)
		depthTexture = true;
	bool stencilTexture = false;
	if (m_stencilTexture != INVALID_OGL_VALUE)
		stencilTexture = true;

	reset();
	generateTextures(width, height, numColorTextures, depthTexture, stencilTexture);
}

void FBO::reset(){
	// delete all textures
	for (unsigned int i = 0; i < m_colorTextures.size(); i++)
	{
		glDeleteTextures(1, &m_colorTextures[i]);
	}
	m_colorTextures.clear();
	if (m_depthTexture != INVALID_OGL_VALUE)
		glDeleteTextures(1, &m_depthTexture);
	if (m_stencilTexture != INVALID_OGL_VALUE)
		glDeleteTextures(1, &m_stencilTexture);
	if (m_frameBufferHandle != INVALID_OGL_VALUE)
		glDeleteFramebuffers(1, &m_frameBufferHandle);

	// reset values
	m_depthTexture = INVALID_OGL_VALUE;
	m_stencilTexture = INVALID_OGL_VALUE;
	m_frameBufferHandle = INVALID_OGL_VALUE;
}

GLuint FBO::getColorTexture(unsigned int index)
{
	// checks if index is allowed
	if (index < m_colorTextures.size())
		return m_colorTextures[index];
	return 0;
}

GLuint FBO::getDepthTexture()
{
	//checks if depth texture exist
	if (m_depthTexture == INVALID_OGL_VALUE)
		return 0;
	return m_depthTexture;
}

GLuint FBO::getStencilTexture()
{
	//checks if stencil texture exist
	if (m_stencilTexture == INVALID_OGL_VALUE)
		return 0;
	return m_stencilTexture;
}