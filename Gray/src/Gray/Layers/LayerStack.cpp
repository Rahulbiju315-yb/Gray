#include "grpch.h"

#include "LayerStack.h"

namespace Gray
{
	void LayerStack::PushLayer(Layer* l)
	{
		stack.push_back(l);
	}

	Layer* LayerStack::PopLayer()
	{
		Layer* l = stack.back();
		stack.pop_back();

		return l;
	}

	Layer* LayerStack::Peek()
	{
		Layer* l = stack.back();

		return l;
	}

	bool LayerStack::RemoveLayer(Layer* l)
	{
		for (Layer* layer : stack)
		{
			if (layer == l)
			{
				stack.erase(std::remove(stack.begin(), stack.end(), l), stack.end());
				return true;
			}
		}
		return false;
	}

	std::vector<Layer*>::iterator LayerStack::begin()
	{
		return stack.begin();
	}

	std::vector<Layer*>::iterator LayerStack::end()
	{
		return stack.end();
	}

	std::vector<Layer*>::reverse_iterator LayerStack::rbegin()
	{
		return stack.rbegin();
	}

	std::vector<Layer*>::reverse_iterator LayerStack::rend()
	{
		return stack.rend();
	}

	Layer* LayerStack::LayerAt(int i)
	{
		return stack.at(i);	
	}
}