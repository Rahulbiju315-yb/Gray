#pragma once
#include "ModelLoader.h"
#include "Gray/Events/EventListener.h"

namespace Gray
{
	class ModelLoaderPool : public EventListener
	{
	public:
		static ModelLoader& GetModelLoader(int n);
		void OnEvent(Event& e, EventType t);

	private:
		ModelLoaderPool();
		static std::vector<ModelLoader> pool;
	};
}