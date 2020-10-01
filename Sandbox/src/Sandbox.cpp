#include "Gray.h"

class Sandbox : public Gray::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}