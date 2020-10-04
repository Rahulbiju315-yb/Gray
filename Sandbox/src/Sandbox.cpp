#include "Gray.h"
#include "Gray/Event/KeyEvent.h"
#include "Gray/Event/KeyListener.h"

#include "grpch.h"

class Sandbox : public Gray::Application, Gray::KeyListener
{
public:
	Sandbox()
	{
		std::cout << "Hello world";
	}

	~Sandbox()
	{

	}
};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}