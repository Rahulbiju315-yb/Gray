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
		Model(const Model& model) = delete;
		Model(Model&& model) noexcept;

		void LoadModel(const std::string& path, const std::string& fName, bool flipTextures=true);

		std::vector<Mesh>::iterator begin();
		std::vector<Mesh>::iterator end();


	private:
		std::vector<Mesh> meshes;
		std::vector<Material> materials;

		std::unordered_map<std::string, NoCopy<Texture>> unique_tex;
		std::string dir; 
		mutable bool isLoaded;
		mutable bool flipTextures;

		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);
		void ProcessMaterial(aiMaterial* material, Mesh& mesh);
		void ProcessTextures(aiMaterial* material, Material& newMat, aiTextureType type);
		void CreateMaterials(const aiScene* scene);

		friend class RenderableModel;
	};
}