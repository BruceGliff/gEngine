#include "TextureGL.h"

#include "ShaderProgram.h"

#include <iostream>

Renderer::TextureGL::TextureGL(std::filesystem::path const& path, ETextureType textureType, GLenum const filter, GLenum const wrapMode) noexcept :
	Resources::Texture_base{path},
	texType{textureType}
{
	GLint tex_mod = 0;
	switch (channels)
	{
	case 4:
		tex_mod = GL_RGBA;
		break;
	case 3:
		tex_mod = GL_RGB;
		break;
	default:
		tex_mod = GL_RGB;
		break;
	}

	glGenTextures(1, &ID);	
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, tex_mod, width, height, 0, tex_mod, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);

	Release();
}

Renderer::TextureGL::~TextureGL()
{
	glDeleteTextures(1, &ID);
}

void Renderer::TextureGL::activateTexture(int texOffset, ShaderProgram const& shader)
{
	// For texture naming: diffuse_textureN .. for each mesh(model?)
	static int diffCount = 1;
	static int specCount = 1;

	// texOffset == 0 means that new mesh starts drawing and counting should restart
	if (!texOffset)
	{
		diffCount = 1;
		specCount = 1;
	}

	glActiveTexture(GL_TEXTURE0 + texOffset); // activate proper texture unit before binding
											  // retrieve texture number (the N in diffuse_textureN)

	std::string name;
	switch (texType)
	{
	case ETextureType::SPECULAR:
		name = std::string{ "texture_specular" + std::to_string(specCount++) };
		break;
	case ETextureType::DIFFUSE:
		name = std::string{ "texture_diffuse" + std::to_string(diffCount++) };
		break;
	default:
		std::cerr << "ERR: Should not be happen while texture drawing!." << std::endl;
	}


	shader.SetInt(name.c_str(), texOffset);
	glBindTexture(GL_TEXTURE_2D, ID);
}
