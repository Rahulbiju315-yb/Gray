#include "grpch.h"
#include "Mesh.h"

namespace Gray
{
    Mesh::Mesh()
    {
    }

    void Mesh::SetupMesh(float* vertices, uint n_vert,
        uint* indices, uint n_ind, const BufferLayout& layout)
    {
        auto vb = NoCopy<VertexBuffer>();
        vb -> LoadBufferData(vertices, n_vert * sizeof(float));

        auto ib = NoCopy<IndexBuffer>();
        ib -> LoadBufferData(indices, n_ind);

        auto va = NoCopy<VertexArray>();
        va -> SetAttribPointers(*vb, layout);

        renderData.vb = std::move(vb);
        renderData.ib = std::move(ib);
        renderData.va = std::move(va);
    }

}