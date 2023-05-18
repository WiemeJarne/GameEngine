#pragma once
#include <any>

namespace dae
{
	class EventListener
	{
	public:
		virtual ~EventListener() = default;
		virtual void OnNotify(std::any data, int eventId, bool isEngineEvent) = 0;
	};
}