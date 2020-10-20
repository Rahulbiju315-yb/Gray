#pragma once

#include "Window.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"


namespace Gray
{
	class GRAY_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const std::string& title, unsigned int width = 1200, unsigned int height = 700);
		~WindowsWindow();

		void OnUpdate() override;
		void OnRender() override;

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;
		const std::string& GetTitle() const override;

		void AddKeyListener(KeyListener *kl) override;
		void AddMouseListener(MouseListener *kl) override;
		void AddWindowListener(WindowListener *kl) override;

		struct WindowData
		{
		public:

			WindowData()
			{
				kls.shrink_to_fit();
				mls.shrink_to_fit();
				wls.shrink_to_fit();
			}

			std::vector<KeyListener*> kls;
			std::vector<MouseListener*> mls;
			std::vector<WindowListener*> wls;
		};

	protected:
		unsigned int width;
		unsigned int height;
		std::string title;
		GLFWwindow *window;

		void OnInit() override;

		WindowData data;
	};
}