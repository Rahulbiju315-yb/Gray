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
	MeshData GetUnitCube2MeshData();
	MeshData GetPyramidMeshData();
	MeshData GetSphereMeshData(float radius, uint rings, uint sectors);

	void CalculateNormals(MeshData& mesh2d);

	uint SizeOfVertices(const MeshData& meshD);
	uint CountOfIndices(const MeshData& meshD);
}