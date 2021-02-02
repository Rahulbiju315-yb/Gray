#include "grpch.h"
#include "ModelMesh.h"

namespace Gray
{

    void ModelMesh::SetupMesh(const MeshData& meshD, const BufferLayout& layout)
    {
        Shared<VertexBuffer> vb = Shared<VertexBuffer>();
        vb -> LoadBufferData(&(meshD.vertices[0]), SizeOfVertices(meshD));

        Shared<IndexBuffer> ib = Shared<IndexBuffer>();
        ib -> LoadBufferData(&(meshD.faces[0].v0), CountOfIndices(meshD));

        Shared<VertexArray> va = Shared<VertexArray>();
        va -> SetAttribPointers(*vb, layout);

        renderData.vb = vb;
        renderData.ib = ib;
        renderData.va = va;
    }

}