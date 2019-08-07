#pragma once

#include "engine_pch.h"

#include "Core.h"
#include "Events/Event.h"

namespace Engine
{

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const char* title = "Engine", unsigned int width = 1280, unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class ENGINE_API Window
	{
	public:
		/*
			(set EventCallbackFunction and other stuff)
			Application  --> Window 
							 EventCallbackFunction <-- event
		*/
		using EventCallbackFunction = std::function<void(Event&)>;

		//should be implimented per platform
		static Window* Create(const WindowProps& props = WindowProps());
		virtual ~Window() { }

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVsync(bool enabled) = 0;
		virtual bool IsVsync() const = 0;

	};

}
