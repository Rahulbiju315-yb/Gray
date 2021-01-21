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

		void SetPath(const std::string path);
		bool TryToLoadModel();

		void LoadScene(const aiScene* path);
		std::string GetPath();

		std::vector<Mesh>::iterator begin();
		std::vector<Mesh>::iterator end();

	private:
		std::vector<Mesh> meshes;
		std::vector<Material> materials;
		std::string path; 

		std::vector<float> LoadVertices(aiMesh* mesh);
		std::vector<uint> LoadIndices(aiMesh* mesh);

		void ProcessNode(aiNode* node, const aiScene* scene, bool flipTextures);
		void CreateMesh(aiMesh* mesh, const aiScene* scene, bool flipTextures);

		void CreateMaterials(const aiScene* scene, bool flipTextures);
		void ProcessTextures(aiMaterial* material, Material& newMat, aiTextureType type, bool flipTextures);

		friend class RenderableModel;
	};
}