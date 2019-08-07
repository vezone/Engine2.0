#pragma once

#include "Event.h"

namespace Engine 
{
	//WindowCloseed, WindowFocused, WindowUnfocused, WindowResized, WindowMoved
	class ENGINE_API WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() {}

		EVENT_CLASS_TYPE(WindowCloseed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API WindowFocusedEvent : public Event
	{
	public:
		WindowFocusedEvent() {}

		EVENT_CLASS_TYPE(WindowFocused)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API WindowUnfocusedEvent : public Event
	{
	public:
		WindowUnfocusedEvent() {}

		EVENT_CLASS_TYPE(WindowUnfocused)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth()  { return m_Width;  }
		inline unsigned int GetHeight() { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class ENGINE_API WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent() {}

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	//AppTick, AppUpdate, AppRender
	class ENGINE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {} 

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}