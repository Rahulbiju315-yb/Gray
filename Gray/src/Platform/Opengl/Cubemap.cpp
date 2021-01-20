#include "grpch.h"
#include "CubeMap.h"
#include "stb_image.h"

std::vector<std::string> faces{"right", "left", "top", "bottom", "back", "front"};

namespace Gray
{
	Cubemap::Cubemap()
		: ID(0)
	{
	}

	void Cubemap::CopyFrom(const Cubemap& src)
	{
		ID = src.ID;
	}

	void Cubemap::CreateIfEmpty()
	{
		if(ID == 0)
			glGenTextures(1, &ID);
	}

	void Cubemap::Free()
	{
		glDeleteTextures(1, &ID);
	}

	void Cubemap::LoadCubeMap(const std::string& path, const std::string ext)
	{
		CreateIfEmpty();
		Bind();

		int width, height, nrChannels;
		unsigned char* data;

		for (unsigned int i = 0; i < 6; i++)
		{
			data = stbi_load((faces[i] + ext).c_str(), &width, &height, &nrChannels, 0);
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void Cubemap::LoadCubeMap(const std::vector<std::string> paths)
	{
		CreateIfEmpty();
		Bind();

		int width, height, nrChannels;
		unsigned char* data;

		for (unsigned int i = 0; i < 6; i++)
		{
			data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void Cubemap::Bind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	}

	void Cubemap::Unbind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	uint Cubemap::GetID() const
	{
		return ID;
	}


}