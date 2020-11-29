#include "grpch.h"

#include "Util.h"

//for debugging purposes only
namespace Gray
{


	void Util::sampleCube(std::unique_ptr<VertexBuffer>& vb,std::unique_ptr<IndexBuffer>& ib, 
		std::unique_ptr<VertexArray>& va, std::shared_ptr<Shader>& shader, bool loadSampleShader)
	{

		static float vertices[] = {
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

		unsigned int indices[36] =
		{
			0, 1, 2, 2, 3, 0, //Back
			4, 5, 6, 6, 7, 4, //Front
			8, 9, 10, 10, 11, 8, //Left
			12, 13, 14, 14, 15, 12, //Right
			16, 17, 18, 18, 19, 16, //Bottom
			20, 21, 22, 22, 23, 20 //Top
		};


		vb = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		ib = std::make_unique<IndexBuffer>(indices, 36);

		BufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);

		va = std::make_unique<VertexArray>(*vb, layout);

		if (loadSampleShader)
		{
			shader = std::make_shared<Shader>("res/shaders/shader.shader");

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