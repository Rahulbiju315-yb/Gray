#pragma once

#include "Gray/Util/ResourceManager.h"
#include "NoCopy.h"
#include "Shared.h"
#include "WeakRef.h"

namespace Gray
{
	class Cubemap
	{
	public:
		void LoadCubeMap(const std::string& path, const std::string ext);
		void LoadCubeMap(const std::vector<std::string> paths);
		
		void Bind() const;
		void Unbind() const;

		uint GetID() const;

	private:
		Cubemap();
		Cubemap(const Cubemap&) =  default;
		Cubemap(Cubemap&&) = default;

		Cubemap& operator=(const Cubemap&) = default;
		Cubemap& operator=(Cubemap&&) = default;

		void CopyFrom(const Cubemap& src);
		void CreateIfEmpty();
		void Free();

		uint ID;

		friend class NoCopy<Cubemap>;
		friend class Shared<Cubemap>;
		friend class WeakRef<Cubemap>;
	};
}