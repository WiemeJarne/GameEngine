#pragma once

namespace dae
{
	template <typename EventType>
	class EventListener
	{
	public:
		EventListener()
		{
			//EventQueueManager::GetInstance().AddListener<EventType>(this);
		}

		virtual ~EventListener()
		{
			//EventQueueManager::GetInstance().RemoveListener<EventType>(this);
		}

		virtual void OnNotify(const EventType* event) = 0;
	};
}