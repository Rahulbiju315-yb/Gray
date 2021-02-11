#pragma once

#include "ModelMesh.h"
#include "assimp/scene.h"
#include "Gray/Mesh/MeshData.h"
#include "Gray/Resources/TextureManager.h"

namespace Gray
{

	class Model
	{
	public:
		Model() = default;

		void LoadScene(const aiScene* scene, const std::string& path, TextureManager& rm);

		std::vector<ModelMesh>::iterator begin();
		std::vector<ModelMesh>::iterator end();

	private:
		std::vector<ModelMesh> meshes;

		MeshData LoadMeshData(aiMesh* mesh);
		void ProcessNode(aiNode* node, const aiScene* scene, const std::vector<Material>& materials);

		friend class RenderableModel;
	};

	void CreateMaterials(const aiScene* scene, std::vector<Material>& materials, const std::string& path,
			TextureManager& rm);

	void ProcessTextures(aiMaterial* material, Material& newMat, aiTextureType type, const std::string& path,
		TextureManager& rm);
		
}