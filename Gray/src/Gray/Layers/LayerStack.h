#pragma once

#include "Layer.h"
#include "grpch.h"

namespace Gray
{
	class LayerStack
	{
	public:
		void PushLayer(Layer* l);
		Layer* PopLayer();
		Layer* Peek();

		bool RemoveLayer(Layer* l);

		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();

		std::vector<Layer*>::reverse_iterator rbegin();
		std::vector<Layer*>::reverse_iterator rend();

		Layer* LayerAt(int i);
		
	protected:
		std::vector<Layer*> stack;
	};
}