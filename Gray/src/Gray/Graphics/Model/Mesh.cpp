#include "grpch.h"
#include "Mesh.h"

namespace Gray
{
    Mesh::Mesh()
    {
    }

    void Mesh::SetupMesh(float* vertices, uint n_vert,
        uint* indices, uint n_ind)
    {
        auto vb = std::make_shared<VertexBuffer>(vertices, n_vert * sizeof(float));
        auto ib = std::make_shared<IndexBuffer>(indices, n_ind);

		BufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);

		auto va = std::make_shared<VertexArray>(*vb, layout);

        data.vb = vb;
        data.ib = ib;
        data.va = va;
    }

}