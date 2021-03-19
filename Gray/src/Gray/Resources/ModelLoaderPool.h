#pragma once
#include "ModelLoader.h"
#include "Gray/Events/EventListener.h"

namespace Gray
{
	class ModelLoaderPool : public EventListener
	{
	public:
		static ModelLoader& GetModelLoader(int n);
		void OnEvent(Event& e) override;

	private:
		ModelLoaderPool();
		static std::vector<ModelLoader> pool;
	};
}