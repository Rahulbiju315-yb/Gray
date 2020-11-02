#include "grpch.h"

#include "Util.h"

//for debugging purposes only
namespace Gray
{
	void Util::sampleObject1(VertexBuffer*& vb, IndexBuffer*& ib, VertexArray*& va, Shader*& shader)
	{
		float vertices[20] =
		{
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // 0
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 1
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 2
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f  // 3
		};

		unsigned int indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};

		vb = new VertexBuffer(vertices, sizeof(vertices));
		ib = new IndexBuffer(indices, 6);

		BufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		va = new VertexArray(*vb, layout);


		shader = new Shader("res/shaders/shader.shader");
		shader->Bind();

		shader->SetUniform("Tex1", 0);
		shader->SetUniform("model", glm::mat4(1.0f));
		shader->SetUniform("view", glm::mat4(1.0f));
		shader->SetUniform("projection", glm::mat4(1.0f));

		shader->Unbind();
	}


	
	void Util::sampleObject2(VertexBuffer*& vb, IndexBuffer*& ib, VertexArray*& va, Shader*& shader, bool loadSampleShader)
	{

		float vertices[] = {
			//Back Side
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, 
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 

			//Front Side
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,

			//Left Side
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

			 //Right Side
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

			 //Bottom Side
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,

			 //Top Side
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		};	

		//float vertices[198];
		//genCube(-0.5f, -0.5f, 0.0f, 1.0f, vertices, 6);

		//for (int i = 0; i < 6; i++)
		//{
		//	vertices[6 * (4 * i + 0) + 3] = 0.0f;
		//	vertices[6 * (4 * i + 0) + 4] = 0.0f;
		//	vertices[6 * (4 * i + 0) + 5] = 0.0f;

		//	vertices[6 * (4 * i + 1) + 3] = 1.0f;
		//	vertices[6 * (4 * i + 1) + 4] = 0.0f;
		//	vertices[6 * (4 * i + 1) + 5] = 0.0f;

		//	vertices[6 * (4 * i + 2) + 3] = 0.0f;
		//	vertices[6 * (4 * i + 2) + 4] = 1.0f;
		//	vertices[6 * (4 * i + 2) + 5] = 0.0f;

		//	vertices[6 * (4 * i + 3) + 3] = 1.0f;
		//	vertices[6 * (4 * i + 3) + 4] = 1.0f;
		//	vertices[6 * (4 * i + 3) + 5] = 0.0f;

		//}


		unsigned int indices[36] =
		{
			0, 1, 2, 2, 3, 0, //Back
			4, 5, 6, 6, 7, 4, //Front
			8, 9, 10, 10, 11, 8, //Left
			12, 13, 14, 14, 15, 12, //Right
			16, 17, 18, 18, 19, 16, //Bottom
			20, 21, 22, 22, 23, 20 //Top
		};

		//std::vector<glm::vec3> tri1;
		//std::vector<glm::vec3> tri2;
		//std::vector<glm::vec3> tri3;

		//tri1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		//tri1.push_back(glm::vec3(0.1f, 0.0f, 0.0f));
		//tri1.push_back(glm::vec3(0.0f, 2.0f, 0.0f));

		//tri2.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		//tri2.push_back(glm::vec3(0.0f, 0.0f, -0.1f));
		//tri2.push_back(glm::vec3(2.0f, 0.0f, 0.0f));

		//tri3.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		//tri3.push_back(glm::vec3(0.0f, 0.1f, 0.0f));
		//tri3.push_back(glm::vec3(0.0f, 0.0f, 2.0f));

		//genTri(tri1, &vertices[144], 6);
		//genTri(tri2, &vertices[144 + 18], 6);
		//genTri(tri3, &vertices[144 + 36], 6);

		//unsigned int debugIndicies[9] =
		//{
		//	24, 25, 26,
		//	27, 28, 29,
		//	30, 31, 32
		//};

		vb = new VertexBuffer(vertices, sizeof(vertices));
		ib = new IndexBuffer(indices, 36);

		BufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);

		va = new VertexArray(*vb, layout);

		if (loadSampleShader)
		{
			shader = new Shader("res/shaders/shader.shader");

			shader->Bind();

			shader->SetUniform("Tex1", 0);
			shader->SetUniform("model", glm::mat4(1.0f));
			shader->SetUniform("view", glm::mat4(1.0f));
			shader->SetUniform("projection", glm::mat4(1.0f));

			shader->Unbind();
		}
	}


	void Util::genCube(float x, float y, float z, float side, float* vertexPositions, int stride)
	{
		genQuad(x, y, z + side, side, Z, &vertexPositions[0], stride); // Front
		genQuad(x, y, z, side, X, &vertexPositions[4 * stride], stride); // Left
		genQuad(x + side, y, z, side, X, &vertexPositions[8 * stride], stride); // Right
		genQuad(x, y, z, side, Y, &vertexPositions[12 * stride], stride); // Bottom
		genQuad(x, y + side, z, side, Y, &vertexPositions[16 * stride], stride); // Top
		genQuad(x, y, z, side, Z, &vertexPositions[20 * stride], stride); // Back
	}

	void Util::genTri(std::vector<glm::vec3> p, float* vertexPositions, int stride)
	{
		for (int i = 0; i < 3; i++)
		{
			vertexPositions[stride * i + 0] = p[i].x;
			vertexPositions[stride * i + 1] = p[i].y;
			vertexPositions[stride * i + 2] = p[i].z;
		}
	}
	void Util::genQuad(float x, float y, float z, float side, int dir, float* vertexPositions, int stride)
	{

		for (int i = 0; i < 4; i++)
		{

			int r = i / 2;

			vertexPositions[stride * i + 0] = x;
			vertexPositions[stride * i + 1] = y;
			vertexPositions[stride * i + 2] = z;

			if (!(dir == X))
			{
				vertexPositions[stride * i + 0] += r * side;
				r = i % 2;
			}

			if (!(dir == Y))
			{
				vertexPositions[stride * i + 1] += r * side;
				r = i % 2;
			}

			if (!(dir == Z))
			{
				vertexPositions[stride * i + 2] += r * side;
			}
		}

	}
}