#pragma once

namespace Gray
{
	class GRAY_API Window
	{
	public:	

		static Window* Create(const std::string& title, unsigned int width = 1200, unsigned int height = 700);

		/*virtual void SetOnInit(void (*funcPtr)) = 0;
		virtual void SetOnUpdate(void (*funcPtr))  = 0;
		virtual void SetOnRender(void (*funcPtr))  = 0;*/
		
		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;

		/*virtual void AddKeyListener(KeyListener* kl)  = 0;
		virtual void AddMouseListener(MouseListener* ml)  = 0;
		virtual void AddWindowListener(WindowListener* wl) = 0;*/

		virtual void SetListener(EventListener *listener);

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual const std::string& GetTitle() const = 0;

	protected:

		/*void(*onInit);
		void(*onUpdate);
		void(*onRender);*/

	};
}