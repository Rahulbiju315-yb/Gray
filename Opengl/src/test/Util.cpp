#include "Util.h"

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
