#include "grpch.h"
#include "Model.h"

#include "Platform/Opengl/Texture.h"
namespace Gray
{

	std::string dir;

	Model::Model() : isLoaded(false)
	{
	}

	//TODO Why is the implicit move constructor not noexcept 
	Model::Model(Model&& model) noexcept
		:meshes(std::move(model.meshes)),
		 materials(std::move(model.materials)),
		 unique_tex(std::move(model.unique_tex)),
		 isLoaded(std::move(model.isLoaded))
	{
	}

	void Model::LoadModel(const std::string& path, const std::string& fName)
	{
		isLoaded = true;

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
		auto& grayMaterial = grayMesh.GetMaterial();
		grayMaterial = *materials[mesh->mMaterialIndex]; // TODO Make Mesh have a pointer to material than material
		
		BufferLayout bl;
		bl.Push<float>(3);
		bl.Push<float>(3);
		bl.Push<float>(2);

		meshes.push_back(grayMesh);
		meshes.back().SetupMesh(&(vertices[0]), (uint)vertices.size(),
								&(indices[0]), (uint)indices.size(), bl);  // TODO PLS fix these warnings abt type conv
	}

	void Model::ProcessTextures(aiMaterial* material, Material& newMat, aiTextureType type)
	{

		void(Material:: * addToMat)(Texture*) = nullptr; 
		switch (type)
		{
		case aiTextureType_DIFFUSE:
			addToMat = &Material::AddDiffuse;
			break;

		case aiTextureType_EMISSIVE:
			addToMat = &Material::AddEmission;
			break;

		case aiTextureType_SPECULAR:
			addToMat = &Material::AddSpecular;
			break;

		default:
			GRAY_CORE_ERROR("Texture Type Not defined in Gray!!!! Defaulting to Diffuse");
			addToMat = &Material::AddDiffuse;

		}
		
	
		for (uint i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString aiPath;
			material->GetTexture(type, i, &aiPath);

			std::string path = std::string(aiPath.C_Str());
			Texture* tex = nullptr;

			if (unique_tex.find(path) == unique_tex.end())
			{
				unique_tex.insert({path, Texture(dir + "/" + path, GL_COMPRESSED_RGBA)});
			}
			tex = &unique_tex[path];
			
			(newMat.*addToMat)(tex);
		}
	}

	void Model::CreateMaterials(const aiScene* scene)
	{
		for (uint i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* material = scene->mMaterials[i];

			materials.push_back(std::make_shared<Material>());
			ProcessTextures(material, *materials[i], aiTextureType_DIFFUSE);
			ProcessTextures(material, *materials[i], aiTextureType_SPECULAR);
			ProcessTextures(material, *materials[i], aiTextureType_EMISSIVE);
		}
	}

	std::vector<std::shared_ptr<Material>>& Model::GetMaterials()
	{
		return materials;
	}
	
	void Model::ProcessMaterial(aiMaterial* material, Mesh& mesh)
	{
		ProcessTextures(material, mesh.GetMaterial(), aiTextureType_DIFFUSE);
		ProcessTextures(material, mesh.GetMaterial(), aiTextureType_SPECULAR);
		ProcessTextures(material, mesh.GetMaterial(), aiTextureType_EMISSIVE);
	}

 }