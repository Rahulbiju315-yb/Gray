#pragma once

#include "TextureLoader.h"
#include "Gray/Events/EventListener.h"

namespace Gray
{
	class TextureLoaderPool : public EventListener
	{
	public:
		static TextureLoader& GetLoader(int n);
		void OnEvent(Event& e, EventType type) override;

	private:
		TextureLoaderPool();
		static std::vector<TextureLoader> pool;
	};
}