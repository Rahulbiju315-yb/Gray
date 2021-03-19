#include "grpch.h"
#include "Surface.h"
#include "Platform/Opengl/BufferLayout.h"
#include "Gray/Image/Image.h"
#include "Gray/Mesh/MeshData.h"

namespace Gray
{
	Surface::Surface(int width, int height, float delta)
	{
		GenerateFlatSurface(width, height, delta);
	}

	void Surface::GenerateFlatSurface(int width, int height, float delta)
	{

	}

	void Surface::GenerateUsingHMap(int width, int height, float delta, const std::string& path)
	{
		MeshData plane = GetPlaneMeshData(width, height, delta);
		
		Image hMap;
		LoadImage(hMap, path);

		for (int i = 0; i < width * height; i++)
		{
			Vertex& v = plane.vertices[i];
			
			int x = static_cast<int>(v.texCoord.x * hMap.width);
			int y = static_cast<int>(v.texCoord.y * hMap.height);
			
			float r = GetR(hMap, x, y);
			float g = GetG(hMap, x, y);
			float b = GetB(hMap, x, y);

			float h = static_cast<float>((r + g + b)) / 3.0f;

			v.pos.y = h;
		}

		CalculateNormals(plane);
		planeMesh = CreateMeshPNT(plane);
	}

	void Surface::Render(const Shader& shader)
	{
		Draw(*planeMesh.va, *planeMesh.ib, shader);
	}
}