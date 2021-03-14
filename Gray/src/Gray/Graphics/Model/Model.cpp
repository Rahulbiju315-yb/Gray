#include "grpch.h"
#include "Model.h"

#include "Platform/Opengl/Texture.h"
#include "Gray/Mesh/Vertex.h"

namespace Gray
{
	void Model::LoadScene(const aiScene* scene, const std::string& path, TextureManager& rm)
	{
		assert(scene != nullptr && "scene null in Model::LoadScene");
		assert(scene->mRootNode != nullptr);

		meshes.clear();
		std::vector<Material> materials;

		CreateMaterials(scene, materials, path, rm);
		ProcessNode(scene->mRootNode, scene, materials);
	}

	std::vector<ModelMesh>::iterator Model::begin()
	{
		return meshes.begin();
	}

	std::vector<ModelMesh>::iterator Model::end()
	{
		return  meshes.end();
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene, const std::vector<Material>& materials)
	{
		for (uint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			
			// Creating the mesh

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

		for (uint i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, materials);
		}
	}

	void ProcessTextures(aiMaterial* material, Material& newMat, aiTextureType type, const std::string& path,
		TextureManager& rm)
	{
		std::string dir = path.substr(0, path.find_last_of('/'));

		void (Material:: * addToMat)(WeakRef<Texture>) = nullptr;
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
		tex = rm.GetTexture(dir + "/" + fnameTexture);
		(newMat.*addToMat)(tex);
		
	}

	//Populates the materials vectors from materials loaded by assimp
	void CreateMaterials(const aiScene* scene, std::vector<Material>& materials,  const std::string& path,
		TextureManager& rm)
	{
		materials.reserve(scene->mNumMaterials);

		for (uint i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* material = scene->mMaterials[i];

			materials.push_back(NewMaterial());
			ProcessTextures(material, materials[i], aiTextureType_DIFFUSE, path, rm);
			ProcessTextures(material, materials[i], aiTextureType_SPECULAR, path, rm);
			ProcessTextures(material, materials[i], aiTextureType_EMISSIVE, path, rm);
		}
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

	Material NewMaterial()
	{
		static uint ID = 1;

		Material m;
		m.ID = ID++;

		return m;
	}

 }