#pragma once

#include "Gray/Graphics/Material.h"
#include "Gray/Graphics/Light/LightingManager.h"
#include "Gray/Mesh/Mesh.h"
#include "Gray/DS/Relations.h"

namespace Gray
{
	using MaterialTable = EntityData<Material, Material, std::string, const char*>;
	using MeshTable =
	struct NullValues
	{
		static const Material nullMaterial;
		static const std::string nullString;
		static const RenderableMesh nullRMesh;
		static const MeshData nullMeshD;
	};

	struct SceneInfo
	{
		SceneInfo()
			: entMaterials(NullValues::nullMaterial, NullValues::nullString, NullValues::nullString.c_str()),
			entRMeshes(NullValues::nullRMesh, NullIndex<Material>(), NullValues::nullString, NullValues::nullString.c_str()),
			entMeshD(NullValues::nullMeshD)
		{
			FixedVector<EntityIndex<Material>> depmat = entRMeshes.GetField<EntityIndex<Material>>();
			FixedVector<EntityIndex<MeshData>> depmesh = entRMeshes.GetField<EntityIndex<MeshData>>();

			entMaterials.AddDependent(depmat);
			entMeshD.AddDependent(depmesh);
		}

		EntityData<MeshData, MeshData> entMeshD;
		EntityData<Material, Material, std::string, const char*> entMaterials;
		EntityData<NoCopyMesh, NoCopyMesh, EntityIndex<Material>, EntityIndex<MeshData>, std::string, const char*> entRMeshes;
		LightingManager lightMan;
	};
}