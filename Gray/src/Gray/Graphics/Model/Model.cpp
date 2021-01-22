#include "grpch.h"
#include "Model.h"

#include "Platform/Opengl/Texture.h"
#include "Gray/Graphics/Resource/ResourceManager.h"

namespace Gray
{

	void Model::SetPath(const std::string path)
	{
		this->path = path;
		AddModelFileForImport(path);
	}

	bool Model::TryToLoadModel()
	{
		return TryLoadSceneForModel(*this);
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

	std::vector<Mesh>::iterator Model::begin()
	{
		return meshes.begin();
	}

	std::vector<Mesh>::iterator Model::end()
	{
		return  meshes.end();
	}

	std::vector<float> Model::LoadVertices(aiMesh* mesh)
	{
		auto vertices{ std::vector<float>() };

		vertices.reserve((size_t)mesh->mNumVertices * 8);

		for (uint i = 0; i < mesh->mNumVertices; i++)
		{
			float px = mesh->mVertices[i].x;
			float py = mesh->mVertices[i].y;
			float pz = mesh->mVertices[i].z;

			vertices.push_back(px);
			vertices.push_back(py);
			vertices.push_back(pz);
			
			if (mesh->mNormals)
			{
				float nx = mesh->mNormals[i].x;
				float ny = mesh->mNormals[i].y;
				float nz = mesh->mNormals[i].z;

				vertices.push_back(nx);
				vertices.push_back(ny);
				vertices.push_back(nz);
			}
			else
			{
				vertices.push_back(1);
				vertices.push_back(1);
				vertices.push_back(1);
			}
			if (mesh->mTextureCoords[0])
			{
				vertices.push_back((mesh->mTextureCoords[0][i]).x);
				vertices.push_back((mesh->mTextureCoords[0][i]).y);
			}
			else
			{
				vertices.push_back(0);
				vertices.push_back(0);
			}
		}

		return vertices;
	}

	std::vector<uint> Model::LoadIndices(aiMesh* mesh)
	{
		auto indices{ std::vector<uint>() };
		
		auto size{ size_t(0) };
		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			size += mesh->mFaces[i].mNumIndices;
		}
		indices.reserve(size);

		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			auto face = mesh->mFaces[i];
			for (uint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		return indices;
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
		std::vector<float> vertices = LoadVertices(mesh);
		std::vector<uint> indices = LoadIndices(mesh);

		Mesh grayMesh;
		grayMesh.material = materials[mesh->mMaterialIndex]; 

		BufferLayout bl;
		bl.Push<float>(3); // Position
		bl.Push<float>(3); // Normal
		bl.Push<float>(2); // Texture Coords

		meshes.push_back(std::move(grayMesh));
		meshes.back().SetupMesh(&(vertices[0]), (uint)vertices.size(),
								&(indices[0]), (uint)indices.size(), bl); 
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
		tex = GetTexture(dir + "/" + fnameTexture);
		(newMat.*addToMat)(tex);
		
	}

	//Populates the materials vectors from materials loaded by assimp
	void Model::CreateMaterials(const aiScene* scene, bool flipTextures)
	{
		materials.reserve(scene->mNumMaterials);

		for (uint i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* material = scene->mMaterials[i];

			materials.push_back(CreateMaterial());
			ProcessTextures(material, materials[i], aiTextureType_DIFFUSE, flipTextures);
			ProcessTextures(material, materials[i], aiTextureType_SPECULAR, flipTextures);
			ProcessTextures(material, materials[i], aiTextureType_EMISSIVE, flipTextures);
		}
	}
 }