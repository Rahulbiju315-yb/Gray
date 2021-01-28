#include "grpch.h"
#include "Mesh.h"

namespace Gray
{
    NoCopyMesh CreateMeshPNT(const MeshData& meshD)
    {
        NoCopyMesh mesh;
		mesh.vb->LoadBufferData(&(meshD.vertices[0]), SizeOfVertices(meshD));
		mesh.ib->LoadBufferData(&(meshD.faces[0].v0), CountOfIndices(meshD));

		BufferLayout bl;
		bl.Push<float>(3);
		bl.Push<float>(3);
		bl.Push<float>(2);

		mesh.va->SetAttribPointers(*mesh.vb, bl);
        return std::move(mesh);
    }
}
