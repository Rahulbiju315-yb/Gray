#pragma once

#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
namespace Gray
{

	class Model
	{
	public:
		Model();

		void LoadModel(const std::string& path, const std::string& fName);

		std::vector<Mesh>::iterator begin();
		std::vector<Mesh>::iterator end();

	private:
		bool isLoaded;

		std::vector<Mesh> meshes;
		
		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}