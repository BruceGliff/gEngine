#include "TextureGL.h"

Renderer::TextureGL::TextureGL(std::string const& path, GLenum const filter, GLenum const wrapMode) noexcept : Resources::Texture_base{path}
{
	// TODO rethink!
	// each texture id should be uniq for at-once-drawable object!
	static GLuint ID_uniq = 0;
	slotID = ID_uniq++;

	GLint tex_mode = 0;
	switch (channels)
	{
	case 4:
		tex_mode = GL_RGBA;
		break;
	case 3:
		tex_mode = GL_RGB;
		break;
	default:
		tex_mode = GL_RGB;
		break;
	}

	glGenTextures(1, &ID);
	// set ap an active texture at the first slot (0 actually) 
	// TODO rethink this part. For each texture should be uniq slot. 
	glActiveTexture(GLindicies_begin + slotID);
	
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, tex_mode, width, height, 0, tex_mode, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Good manners to disable active texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

Renderer::TextureGL::~TextureGL()
{
	glDeleteTextures(1, &ID);
}

void Renderer::TextureGL::bind() const noexcept
{
	glActiveTexture(GLindicies_begin + slotID);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Renderer::TextureGL::unbind() noexcept
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
