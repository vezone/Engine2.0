#pragma once

#include "Event.h"

namespace Engine
{
	class ENGINE_API MouseMovedEvent : public Event
	{
	private:
		float m_MouseX;
		float m_MouseY;

	public:
		
		MouseMovedEvent(float mouseX, float mouseY)
			: m_MouseX(mouseX), m_MouseY(mouseY) { }
		
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
		EVENT_CLASS_TYPE(MouseMoved)
	};

	class ENGINE_API MouseScrolledEvent : public Event
	{
	private:
		float m_XOffset;
		float m_YOffset;

	public:

		MouseScrolledEvent(float XOffset, float YOffset)
			: m_XOffset(XOffset), m_YOffset(YOffset) { }

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
		EVENT_CLASS_TYPE(MouseScrolled)
	};

	class ENGINE_API MouseButtonEvent : public Event
	{
	protected:
		int m_Button;

		MouseButtonEvent(int button)
			: m_Button(button) { }
	public:

		inline int GetButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
	};

	class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << GetButton();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed);
	};

	class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << GetButton();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased);
	};

}