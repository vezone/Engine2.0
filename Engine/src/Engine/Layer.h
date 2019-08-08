#pragma once

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace Engine
{
	class ENGINE_API Layer
	{
	protected:
		std::string m_DebugName;

	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {};
		inline const std::string& GetName() const { return m_DebugName; }

	};
}