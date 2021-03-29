#pragma once

#include "Gray/Mesh/Mesh.h"
namespace Gray
{
	class MeshList
	{
	public:
		MeshList()
		{

		}

		void Add(RenderableMesh&& rmesh, std::string name, uint matInd)
		{
			rmeshes.push_back(rmesh);

			bool recalc = names.size() == names.capacity();
			names.push_back(name);

			if (recalc)
			{
				for (int i = 0; i < cnames.size(); i++)
				{
					cnames[i] = names[i].c_str();
				}
			}

			cnames.push_back(names.back().c_str());
			matInds.push_back(matInd);
		}

		const std::vector<const char*>& GetCNames() const
		{
			return cnames;
		}

		std::vector<RenderableMesh>& GetRMeshes()
		{
			return rmeshes;
		}

		void ReplaceMatInd(uint from, uint to)
		{
			for (uint& matInd : matInds)
			{
				if (matInd == from)
					matInd = to;
			}
		}

	private:
		std::vector<RenderableMesh> rmeshes;
		std::vector<std::string> names;
		std::vector<const char*> cnames;
		std::vector<uint> matInds;
	};
}