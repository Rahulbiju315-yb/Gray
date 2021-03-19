#include "grpch.h"
#include "MeshData.h"
#include "glm/glm.hpp"

namespace Gray
{
	MeshData GetPlaneMeshData(int width, int height, float delta)
	{
		MeshData mesh;

		int numVertices = width * height;
		mesh.vertices.reserve(numVertices);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Vertex v;

				v.pos = glm::vec3(j * delta, 0, i * delta);
				v.normal = glm::vec3(0);
				v.texCoord = glm::vec2((float)i / width, (float)j / height);

				mesh.vertices.push_back(v);
			}
		}

		int numFaces = 2 * (width - 1) * (height - 1);
		mesh.faces.reserve(numFaces);
		int c = 0;
		for (int i = 0; i < height - 1; i++)
		{
			for (int j = 0; j < width - 1; j++)
			{
				Face f1; Face f2;

				f1.v0 = c;                f1.v1 = 1 + c;        f1.v2 = width + c + 1;
				f2.v0 = width + 1 + c;    f2.v1 = width + c;    f2.v2 = c;

				mesh.faces.push_back(f1);
				mesh.faces.push_back(f2);

				c++;
			}
		}

		return mesh;
	}

	MeshData GetUnitCube1MeshData()
	{
		MeshData mesh;
		Vertex v;
		
		v.pos = glm::vec3(-1.0f, -1.0f, -1.0f); // 0 
		v.texCoord = glm::vec2(1, 0);
		mesh.vertices.push_back(v);

		v.pos = glm::vec3(1.0f, -1.0f, -1.0f); // 1 
		v.texCoord = glm::vec2(1, 1);
		mesh.vertices.push_back(v);

		v.pos = glm::vec3(1.0f, 1.0f, -1.0f);  // 2
		v.texCoord = glm::vec2(0, 0);
		mesh.vertices.push_back(v);

		v.pos = glm::vec3(-1.0f, 1.0f, -1.0f); // 3
		v.texCoord = glm::vec2(0, 1);
		mesh.vertices.push_back(v);

		v.pos = glm::vec3(-1.0f, -1.0f, 1.0f); // 4
		v.texCoord = glm::vec2(0, 0);
		mesh.vertices.push_back(v);

		v.pos = glm::vec3(1.0f, -1.0f, 1.0f);  // 5
		v.texCoord = glm::vec2(0, 1);
		mesh.vertices.push_back(v);

		v.pos = glm::vec3(1.0f, 1.0f, 1.0f);   // 6
		v.texCoord = glm::vec2(1, 1);
		mesh.vertices.push_back(v);

		v.pos = glm::vec3(-1.0f, 1.0f, 1.0f);  // 7
		v.texCoord = glm::vec2(1, 1);
		mesh.vertices.push_back(v);

		Face f1; Face f2;

		f1.v0 = 1;	f1.v1 = 0;	f1.v2 = 3;
		f2.v0 = 3;	f2.v1 = 2;	f2.v2 = 1;
		mesh.faces.push_back(f1); 
		mesh.faces.push_back(f2); // Back

		f1.v0 = 7;	f1.v1 = 6;	f1.v2 = 2;
		f2.v0 = 2;	f2.v1 = 3;	f2.v2 = 7;
		mesh.faces.push_back(f1);
		mesh.faces.push_back(f2); // Top

		f1.v0 = 5;	f1.v1 = 1;	f1.v2 = 2;
		f2.v0 = 2;	f2.v1 = 6;	f2.v2 = 5;
		mesh.faces.push_back(f1);
		mesh.faces.push_back(f2); // Right

		f1.v0 = 0;	f1.v1 = 4;	f1.v2 = 7;
		f2.v0 = 7;	f2.v1 = 3;	f2.v2 = 0;
		mesh.faces.push_back(f1);
		mesh.faces.push_back(f2); // Left

		f1.v0 = 5;	f1.v1 = 4;	f1.v2 = 0;
		f2.v0 = 0;	f2.v1 = 1;	f2.v2 = 5;
		mesh.faces.push_back(f1);
		mesh.faces.push_back(f2); // Bottom

		f1.v0 = 4;	f1.v1 = 5;	f1.v2 = 6;
		f2.v0 = 6;	f2.v1 = 7;	f2.v2 = 4;
		mesh.faces.push_back(f1);
		mesh.faces.push_back(f2); // Front

		return mesh;
	}

	MeshData GetUnitCube2MeshData()
	{
		glm::vec3 p1 { -1.0f, -1.0f, -1.0f };
		glm::vec3 p2 { +1.0f, -1.0f, -1.0f };
		glm::vec3 p3 { +1.0f, +1.0f, -1.0f };
		glm::vec3 p4 { -1.0f, +1.0f, -1.0f };

		glm::vec3 p5 { -1.0f, -1.0f, +1.0f };
		glm::vec3 p6 { +1.0f, -1.0f, +1.0f };
		glm::vec3 p7 { +1.0f, +1.0f, +1.0f };
		glm::vec3 p8 { -1.0f, +1.0f, +1.0f };

		glm::vec3 nBack    { 0,  0, -1};
		glm::vec3 nTop     { 0,  1,  0};
		glm::vec3 nRight   { 1,  0,  0};
		glm::vec3 nLeft    {-1,  0,  0};
		glm::vec3 nBottom  { 0, -1,  0};
		glm::vec3 nFront   { 0,  0,  1};

		glm::vec2 tBottomLeft  { 0, 0 };
		glm::vec2 tBottomRight { 1, 0 };
		glm::vec2 tTopRight    { 1, 1 };
		glm::vec2 tTopLeft     { 0, 1 };

		MeshData meshD;
		meshD.vertices.push_back({p2, nBack, tBottomLeft});
		meshD.vertices.push_back({p1, nBack, tBottomRight});
		meshD.vertices.push_back({p4, nBack, tTopRight});
		meshD.vertices.push_back({p3, nBack, tTopLeft});

		meshD.vertices.push_back({p6, nRight, tBottomLeft});
		meshD.vertices.push_back({p2, nRight, tBottomRight});
		meshD.vertices.push_back({p3, nRight, tTopRight});
		meshD.vertices.push_back({p7, nRight, tTopLeft});

		meshD.vertices.push_back({p8, nTop, tBottomLeft});
		meshD.vertices.push_back({p7, nTop, tBottomRight});
		meshD.vertices.push_back({p3, nTop, tTopRight});
		meshD.vertices.push_back({p4, nTop, tTopLeft});

		meshD.vertices.push_back({p1, nLeft, tBottomLeft});
		meshD.vertices.push_back({p5, nLeft, tBottomRight});
		meshD.vertices.push_back({p8, nLeft, tTopRight});
		meshD.vertices.push_back({p4, nLeft, tTopLeft});

		meshD.vertices.push_back({p6, nBottom, tBottomLeft});
		meshD.vertices.push_back({p5, nBottom, tBottomRight});
		meshD.vertices.push_back({p1, nBottom, tTopRight});
		meshD.vertices.push_back({p2, nBottom, tTopLeft});

		meshD.vertices.push_back({p5, nFront, tBottomLeft});
		meshD.vertices.push_back({p6, nFront, tBottomRight});
		meshD.vertices.push_back({p7, nFront, tTopRight});
		meshD.vertices.push_back({p8, nFront, tTopLeft});

		// Back								 Right
		meshD.faces.push_back({0, 1, 2});	 meshD.faces.push_back({4, 5, 6});
		meshD.faces.push_back({2, 3, 0});	 meshD.faces.push_back({6, 7, 4});
											 
		// Top                               Left
		meshD.faces.push_back({8, 9, 10});	 meshD.faces.push_back({12, 13, 14});
		meshD.faces.push_back({10, 11, 8});	 meshD.faces.push_back({14, 15, 12});

		// Bottom							 Front
		meshD.faces.push_back({16, 17, 18}); meshD.faces.push_back({20, 21, 22});
		meshD.faces.push_back({18, 19, 16}); meshD.faces.push_back({22, 23, 20});

		return meshD;
	}

	MeshData GetPyramidMeshData()
	{
		MeshData meshD;
		
		glm::vec3 p1 = {-0.5f, 0   , -0.5f};
		glm::vec3 p2 = {+0.5f, 0   , -0.5f};
		glm::vec3 p3 = {+0.5f, 0   , +0.5f};
		glm::vec3 p4 = {-0.5f, 0   , +0.5f};
		glm::vec3 p5 = { 0   , 1.0f,     0};

		
		meshD.vertices.push_back(Vertex{ p1, {0, 0, 0}, {0, 0} });
		meshD.vertices.push_back(Vertex{ p2, {0, 0, 0}, {0, 0} });
		meshD.vertices.push_back(Vertex{ p3, {0, 0, 0}, {0, 0} });
		meshD.vertices.push_back(Vertex{ p4, {0, 0, 0}, {0, 0} });
		meshD.vertices.push_back(Vertex{ p5, {0, 0, 0}, {0, 0} });

		meshD.faces.push_back(Face{0, 1, 2});
		meshD.faces.push_back(Face{2, 3, 0});

		meshD.faces.push_back(Face{ 0, 1, 4 });
		meshD.faces.push_back(Face{ 1, 2, 4 });
		meshD.faces.push_back(Face{ 2, 3, 4 });

		return meshD;
	}

	uint VIndexOnSphere(uint r, uint s, uint rings, uint sectors)
	{
		return r * sectors + s;
	}

	MeshData GetSphereMeshData(float radius, uint rings, uint sectors)
	{
		MeshData meshD;
		meshD.vertices.reserve(rings * sectors);
		meshD.faces.reserve(rings * sectors * 2);

		constexpr float PI = glm::radians(180.0f);
		float dtheta = 2 * PI / (sectors - 1);
		float dphi = PI / (rings - 1);

		
		for (uint r = 0; r < rings; r++)
		{
			float phi = r * dphi - PI / 2;
	
			for (uint s = 0; s < sectors; s++)
			{
				float theta = s * dtheta;

				float x = radius * glm::cos(phi) * cos(theta);
				float y = radius * glm::sin(phi);
				float z = radius * glm::cos(phi) * sin(theta);

				float u = theta / (2 * PI);
				float v = y / (2.0f * radius) + 0.5f;
				assert(u >= 0 && u <= 1);
				assert(v >=0 && v <= 1);
				meshD.vertices.push_back(Vertex{ {x, y, z}, {x, y, z}, {u, v} });
			}
		}

		for (uint r = 0; r < rings - 1; r++)
		{
			for (uint s = 0; s < sectors - 1; s++)
			{
				uint i1 = VIndexOnSphere(r, s, rings, sectors);
				uint i2 = VIndexOnSphere(r, s + 1, rings, sectors);
				uint i3 = VIndexOnSphere(r + 1, s, rings, sectors);
				uint i4 = VIndexOnSphere(r + 1, s + 1, rings, sectors);

				Face f1{ i2, i1, i3 };
				Face f2{ i3, i4, i2 };

				meshD.faces.push_back(f1);
				meshD.faces.push_back(f2);
			}
		}

		return meshD;
	}

	void CalculateNormals(MeshData& mesh2d)
	{
		for (Face& face : mesh2d.faces)
		{
			Vertex& v0 = mesh2d.vertices[face.v0];
			Vertex& v1 = mesh2d.vertices[face.v1];
			Vertex& v2 = mesh2d.vertices[face.v2];

			glm::vec3 O = v1.pos;

			glm::vec3 a = v0.pos - O;
			glm::vec3 b = v2.pos - O;

			glm::vec3 normal = glm::cross(a, b);

			v0.normal += normal;
			v1.normal += normal;
			v2.normal += normal;
		}
	}

	uint SizeOfVertices(const MeshData& meshD)
	{
		return static_cast<uint>(meshD.vertices.size() * 8 * sizeof(float));
	}

	uint CountOfIndices(const MeshData& meshD)
	{
		return static_cast<uint>(3 * meshD.faces.size());
	}
}