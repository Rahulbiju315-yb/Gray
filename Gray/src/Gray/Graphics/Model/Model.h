#pragma once

#include "ModelMesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Gray/Mesh/MeshData.h"

namespace Gray
{

	class Model
	{
	public:
		Model() = default;

		void SetPath(const std::string path);
		bool TryToLoadModel();

		void LoadScene(const aiScene* path);
		std::string GetPath();

		std::vector<ModelMesh>::iterator begin();
		std::vector<ModelMesh>::iterator end();

	private:
		std::vector<ModelMesh> meshes;
		std::vector<Material> materials;
		std::string path; 

		MeshData LoadMeshData(aiMesh* mesh);

		void ProcessNode(aiNode* node, const aiScene* scene, bool flipTextures);
		void CreateMesh(aiMesh* mesh, const aiScene* scene, bool flipTextures);

		void CreateMaterials(const aiScene* scene, bool flipTextures);
		void ProcessTextures(aiMaterial* material, Material& newMat, aiTextureType type, bool flipTextures);

		friend class RenderableModel;
	};
}