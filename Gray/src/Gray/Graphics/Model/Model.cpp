#include "grpch.h"
#include "Model.h"

#include "Platform/Opengl/Texture.h"
#include "Gray/Graphics/ResourceManager.h"
namespace Gray
{

	Model::Model() : isLoaded(false), flipTextures(true)
	{
	}

	//TODO Why is the implicit move constructor not noexcept 
	Model::Model(Model&& model) noexcept
		:meshes(std::move(model.meshes)),
		materials(std::move(model.materials)),
		unique_tex(std::move(model.unique_tex)),
		isLoaded(std::move(model.isLoaded)),
		flipTextures(model.flipTextures)
	{
	
	}

	void Model::LoadModel(const std::string& path, const std::string& fName, bool flipTextures)
	{
		GRAY_CORE_INFO("Reading model from path : " + path + "\nFile Name : " + fName);
		isLoaded = true;
		this->flipTextures = flipTextures;

		Assimp::Importer importer;
		auto scene = importer.ReadFile(path + "/" + fName, aiProcess_Triangulate | aiProcess_FlipUVs);

		dir = path;

		CreateMaterials(scene);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			GRAY_ERROR("Failed to load model " + path + "/" + fName);
			isLoaded = false;
		}
		else
		{
			ProcessNode(scene->mRootNode, scene);
		}

	}

	std::vector<Mesh>::iterator Model::begin()
	{
		return meshes.begin();
	}

	std::vector<Mesh>::iterator Model::end()
	{
		return  meshes.end();
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (uint i = 0; i < node->mNumMeshes; i++)
		{
			auto mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene);
		}

		for (uint i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		auto vertices{ std::vector<float>() };
		auto indices{ std::vector<uint>() };

		vertices.reserve((size_t)mesh->mNumVertices * 8);

		for (uint i = 0; i < mesh->mNumVertices; i++)
		{
			float px = mesh->mVertices[i].x;
			float py = mesh->mVertices[i].y;
			float pz = mesh->mVertices[i].z;

			vertices.push_back(px);
			vertices.push_back(py);
			vertices.push_back(pz);
			
			float nx = mesh->mNormals[i].x;
			float ny = mesh->mNormals[i].y;
			float nz = mesh->mNormals[i].z;

			vertices.push_back(nx);
			vertices.push_back(ny);
			vertices.push_back(nz);

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

		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			auto face = mesh->mFaces[i];
			for (uint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

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

	void Model::ProcessTextures(aiMaterial* material, Material& newMat, aiTextureType type)
	{

		void(Material:: * addToMat)(const Texture*) = nullptr;
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

		const Texture* tex = nullptr;
		std::string path = std::string(aiPath.C_Str());
		tex = GetTexture(dir + "/" + path, flipTextures);

		(newMat.*addToMat)(tex);
		
	}

	//Populates the materials vectors from materials loaded by assimp
	void Model::CreateMaterials(const aiScene* scene)
	{
		materials.reserve(scene->mNumMaterials);

		for (uint i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* material = scene->mMaterials[i];

			materials.push_back(CreateMaterial());
			ProcessTextures(material, materials[i], aiTextureType_DIFFUSE);
			ProcessTextures(material, materials[i], aiTextureType_SPECULAR);
			ProcessTextures(material, materials[i], aiTextureType_EMISSIVE);
		}
	}

	//Get texture maps for a material
	void Model::ProcessMaterial(aiMaterial* material, Mesh& mesh)
	{
		ProcessTextures(material, mesh.material, aiTextureType_DIFFUSE);
		ProcessTextures(material, mesh.material, aiTextureType_SPECULAR);
		ProcessTextures(material, mesh.material, aiTextureType_EMISSIVE);
	}
 }