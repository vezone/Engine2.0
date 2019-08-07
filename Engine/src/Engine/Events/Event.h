#pragma once
#include "engine_pch.h"
#include "Engine/Core.h"

namespace Engine
{
	enum class EventType
	{
		None = 0,
		/*Window events*/
		WindowCloseed, WindowFocused, WindowUnfocused, WindowResized, WindowMoved,
		/*App events*/
		AppTick, AppUpdate, AppRender, 
		/*Key events*/
		KeyPressed, KeyReleased, KeyTyped,
		/*Mouse events*/
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};


#define EVENT_CLASS_TYPE(event_type) static EventType GetStaticType() { return EventType::##event_type; }\
									 virtual EventType GetEventType() const override { return GetStaticType(); }\
									 virtual const char* GetName() const override { return #event_type; }

#define EVENT_CLASS_CATEGORY(event_category) virtual int GetCategoryFlags() const override { return event_category; }

	class ENGINE_API Event
	{
	public:
		bool Handled = false;
		
		virtual EventType GetEventType() const = 0;
		/*Debug mode only*/
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		/*Debug mode only*/
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory eventCategory)
		{
			return GetCategoryFlags() & eventCategory;
		}

	private:
		friend class EventDispatcher;

	};

	class EventDispatcher
	{
	private:
		Event& m_Event;
		
		template <typename T>
		using EventFunction = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template <typename T>
		bool Dispatch(EventFunction<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)& m_Event);
				return true;
			}
			return false;
		}
	};

}