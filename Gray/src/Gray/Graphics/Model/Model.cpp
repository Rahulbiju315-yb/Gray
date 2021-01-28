#include "grpch.h"
#include "Model.h"

#include "Platform/Opengl/Texture.h"
#include "Gray/Graphics/Resource/ResourceManager.h"
#include "Gray/Mesh/Vertex.h"

namespace Gray
{

	void Model::SetPath(const std::string path)
	{
		this->path = path;
		RM_AddModelFileForImport(path);
	}

	bool Model::TryToLoadModel()
	{
		return RM_TryLoadModel(*this);
	}

	void Model::LoadScene(const aiScene* scene)
	{
		assert(scene != nullptr && "scene null in Model::LoadScene");

		meshes.clear();
		materials.clear();

		assert(scene->mRootNode != nullptr);

		CreateMaterials(scene, true);
		ProcessNode(scene->mRootNode, scene, true);
	}

	std::string Model::GetPath()
	{
		return path;
	}

	std::vector<ModelMesh>::iterator Model::begin()
	{
		return meshes.begin();
	}

	std::vector<ModelMesh>::iterator Model::end()
	{
		return  meshes.end();
	}

	MeshData Model::LoadMeshData(aiMesh* mesh)
	{
		MeshData meshD;
		meshD.vertices.reserve((size_t)mesh->mNumVertices * 8);

		Vertex v;
		 
		// Loading vertices
		bool hasNormals = (mesh->mNormals != nullptr);
		for (uint i = 0; i < mesh->mNumVertices; i++)
		{
			v.pos = glm::vec3(
				mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z
			);


			if (hasNormals)
			{
				v.normal = glm::vec3(
					mesh->mNormals[i].x,
					mesh->mNormals[i].y,
					mesh->mNormals[i].z
				);
			}
			else
			{
				v.normal = glm::vec3(0);
			}

			if (mesh->mTextureCoords[0])
			{
				v.texCoord = glm::vec2(
					(mesh->mTextureCoords[0][i]).x,
					(mesh->mTextureCoords[0][i]).y
				);
			}
			else
			{
				v.texCoord = glm::vec2(0);
			}

			meshD.vertices.push_back(v);
		}

		// Loading faces
		int size = 0;
		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			size += mesh->mFaces[i].mNumIndices;
		}
		meshD.faces.reserve(size / 3);

		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			auto face = mesh->mFaces[i];
			for (uint j = 0; j < face.mNumIndices; j+=3)
			{
				meshD.faces.push_back(Face{
					face.mIndices[j],
					face.mIndices[j + 1],
					face.mIndices[j + 2]
				});
			}
		}
		return meshD;
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene, bool flipTextures)
	{
		for (uint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			CreateMesh(mesh, scene, flipTextures);
		}

		for (uint i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, flipTextures);
		}
	}

	
	void Model::CreateMesh(aiMesh* mesh, const aiScene* scene, bool flipTextures)
	{
		MeshData meshD = LoadMeshData(mesh);

		ModelMesh modelMesh;
		modelMesh.material = materials[mesh->mMaterialIndex]; 

		BufferLayout bl;
		bl.Push<float>(3); // Position
		bl.Push<float>(3); // Normal
		bl.Push<float>(2); // Texture Coords

		modelMesh.SetupMesh(meshD, bl);

		meshes.push_back(modelMesh);
	}

	void Model::ProcessTextures(aiMaterial* material, Material& newMat, aiTextureType type, bool flipTextures)
	{
		std::string dir = path.substr(0, path.find_last_of('/'));

		void(Material:: * addToMat)(WeakRef<Texture>) = nullptr;
		switch (type)
		{
		case aiTextureType_DIFFUSE:
			addToMat = &Material::SetDiffuse;
			break;

		case aiTextureType_EMISSIVE:
			addToMat = &Material::SetEmission;
			break;

		case aiTextureType_SPECULAR:
			addToMat = &Material::SetSpecular;
			break;

		default:
			GRAY_CORE_ERROR("Texture Type Not defined in Gray!!!! Defaulting to Diffuse");
			addToMat = &Material::SetDiffuse;

		}

		//Load the last texture of the given type, since Gray can only handle
		//materials with single texture for each texture maps.
		uint i = material->GetTextureCount(type) - 1;

		aiString aiPath;
		material->GetTexture(type, i, &aiPath);

		WeakRef<Texture> tex;
		std::string fnameTexture = std::string(aiPath.C_Str());
		tex = RM_GetTexture(dir + "/" + fnameTexture);
		(newMat.*addToMat)(tex);
		
	}

	//Populates the materials vectors from materials loaded by assimp
	void Model::CreateMaterials(const aiScene* scene, bool flipTextures)
	{
		materials.reserve(scene->mNumMaterials);

		for (uint i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* material = scene->mMaterials[i];

			materials.push_back(RM_CreateMaterial());
			ProcessTextures(material, materials[i], aiTextureType_DIFFUSE, flipTextures);
			ProcessTextures(material, materials[i], aiTextureType_SPECULAR, flipTextures);
			ProcessTextures(material, materials[i], aiTextureType_EMISSIVE, flipTextures);
		}
	}
 }