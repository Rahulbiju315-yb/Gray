#include "Gray.h"
#include "iostream"
#include "Gray/Event/KeyEvent.h"
#include "Gray/Event/KeyListener.h"

class Sandbox : public Gray::Application, Gray::KeyListener
{
public:
	Sandbox()
	{
		Gray::KeyPressedEvent event(0, 0);
		this->OnEvent(event);
	}

	~Sandbox()
	{

	}

	void OnKeyPressed(Gray::KeyPressedEvent& e) const 
	{
		GRAY_INFO("Yup this works");
	}
};

Gray::Application* Gray::CreateApplication()
{
	return new Sandbox();
}