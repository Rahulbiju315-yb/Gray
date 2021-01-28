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
		hMap.path = path;
		LoadImage(hMap);

		for (int i = 0; i < width * height; i++)
		{
			Vertex& v = plane.vertices[i];
			
			int x = (int)(v.texCoord.x * hMap.width);
			int y = (int)(v.texCoord.y * hMap.height);
			
			float r = GetR(hMap, x, y);
			float g = GetG(hMap, x, y);
			float b = GetB(hMap, x, y);

			float h = (r + g + b) / 3.0;

			v.pos.y = h;
		}

		CalculateNormals(plane);

		vb->LoadBufferData(&(plane.vertices[0]), plane.vertices.size() * 8 * sizeof(float));
		ib->LoadBufferData(&(plane.faces[0].v0), 3 * plane.faces.size());

		BufferLayout bl;
		bl.Push<float>(3);
		bl.Push<float>(3);
		bl.Push<float>(2);

		va->SetAttribPointers(*vb, bl);
	}

	void Surface::Render(const Shader& shader)
	{
		Draw(*va, *ib, shader);
	}

}