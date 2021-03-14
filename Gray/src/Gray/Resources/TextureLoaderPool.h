#pragma once

#include "TextureLoader.h"
#include "Gray/Events/EventListener.h"

namespace Gray
{
	class TextureLoaderPool : public EventListener
	{
	public:
		static TextureLoader& GetLoader(uint n);
		void OnEvent(Event& e, EventType type) override;

	private:
		TextureLoaderPool();
	};
}