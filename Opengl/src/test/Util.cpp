#include "Util.h"
#include <iostream>


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
	layout.push<float>(3);
	layout.push<float>(2);

	va = new VertexArray(*vb, layout);


	shader = new Shader("res/shaders/shader.shader");
	shader->bind();

	shader->setUniform("Tex1", 0);
	shader->setUniform("model", glm::mat4(1.0f));
	shader->setUniform("view", glm::mat4(1.0f));
	shader->setUniform("projection", glm::mat4(1.0f));

	shader->unbind();
}

void Util::sampleObject2(VertexBuffer*& vb, IndexBuffer*& ib, VertexArray*& va, Shader*& shader)
{
	

	float vertices[120];
	genCube(-0.5f, -0.5f, 0.0f, 1.0f, vertices, 5);

	for (int i = 0; i < 6; i++)
	{
		vertices[5 * (4 * i + 0) + 3] = 0.0f;
		vertices[5 * (4 * i + 0) + 4] = 0.0f;

		vertices[5 * (4 * i + 1) + 3] = 1.0f;
		vertices[5 * (4 * i + 1) + 4] = 0.0f;

		vertices[5 * (4 * i + 2) + 3] = 0.0f;
		vertices[5 * (4 * i + 2) + 4] = 1.0f;

		vertices[5 * (4 * i + 3) + 3] = 1.0f;
		vertices[5 * (4 * i + 3) + 4] = 1.0f;

	}

	unsigned int indices[36] =
	{
		0, 1, 3, 3, 2, 0, // Front Side
		4, 5, 7, 7, 6, 4, // Left Side
		8, 9, 11, 11, 10, 8, // Right Side
		12, 13, 15, 15, 14, 12, // Bottom Side
		16, 17, 19, 19, 18, 16, // Top Side
		20, 21, 23, 23, 22, 20, // Back Side
	};

	vb = new VertexBuffer(vertices, sizeof(vertices));
	ib = new IndexBuffer(indices, 36);

	BufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);

	va = new VertexArray(*vb, layout);


	shader = new Shader("res/shaders/shader.shader");
	shader->bind();

	shader->setUniform("Tex1", 0);
	shader->setUniform("model", glm::mat4(1.0f));
	shader->setUniform("view", glm::mat4(1.0f));
	shader->setUniform("projection", glm::mat4(1.0f));

	shader->unbind();
}


void Util::genCube(float x, float y, float z, float side, float* vertexPositions, int stride)
{
	genQuad(x , y, z + side, side, Z, &vertexPositions[0], stride); // Front
	genQuad(x , y, z, side, X, &vertexPositions[4 * stride], stride); // Left
	genQuad(x + side, y, z, side, X, &vertexPositions[8 * stride], stride); // Right
	genQuad(x , y, z, side, Y, &vertexPositions[12 * stride], stride); // Bottom
	genQuad(x , y + side, z, side, Y, &vertexPositions[16 * stride], stride); // Top
	genQuad(x , y, z, side, Z, &vertexPositions[20 * stride], stride); // Back
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