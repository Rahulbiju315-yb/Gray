#pragma once
#include "Vertex.h"

namespace Gray
{
	struct MeshData
	{
		std::vector <Vertex> vertices;
		std::vector <Face> faces;
	};

	MeshData GetPlaneMeshData(int width, int height, float delta);
	MeshData GetUnitCube1MeshData();
	MeshData GetUnitCube2MeshdData();

	void CalculateNormals(MeshData& mesh2d);

	size_t SizeOfVertices(const MeshData& meshD);
	size_t CountOfIndices(const MeshData& meshD);
}