#pragma once

#include "Gray/Graphics/Material.h"
#include "Gray/Graphics/Light/LightingManager.h"
#include "Gray/Mesh/Mesh.h"
#include "Gray/DS/Relations.h"

namespace Gray
{
	struct NullValues
	{
		static const Material nullMaterial;
		static const std::string nullString;
		static const RenderableMesh nullRMesh;
	};

	struct SceneInfo
	{
		SceneInfo()
			: materialEntities(NullValues::nullMaterial, NullValues::nullString, NullValues::nullString.c_str()),
			rmeshEntities(NullValues::nullRMesh, NullIndex<Material>(), NullValues::nullString, NullValues::nullString.c_str())
		{
			FixedVector<EntityIndex<Material>> dep = rmeshEntities.GetField<EntityIndex<Material>>();
			materialEntities.AddDependent(dep);
		}

		EntityData<Material, Material, std::string, const char*> materialEntities;
		EntityData<RenderableMesh, RenderableMesh, EntityIndex<Material>, std::string, const char*> rmeshEntities;
	};
}