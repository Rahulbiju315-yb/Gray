#pragma once
#include "Test.h"
#include "Gray/Events/Event.h"
namespace Test
{
	class TestName
	{
	public :
		virtual void OnInit()
		{
		}

		virtual void PreRender(float dt)
		{
		}

		virtual void Render(float dt)
		{
		}

		virtual void PostRender(float dt)
		{
		}

		virtual void OnEvent(Gray::Event& e) 
		{
		}
	};
}