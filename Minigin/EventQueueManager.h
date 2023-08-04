#pragma once
#include "Singleton.h"
#include "EventQueue.h"
#include "BaseEvent.h"
#include <unordered_map>
#include <typeindex>

namespace dae
{
	class EventQueueManager final : public Singleton<EventQueueManager>
	{
	public:
		template <typename EventType>
		void AddEvent(std::unique_ptr<EventType> pEvent)
		{
			GetEventQueue<EventType>()->AddEvent(std::move(pEvent));
			m_EventWasAdded = true;
		}
	
		template <typename EventType>
		void AddListener(EventListener<EventType>* pEventListener)
		{
			GetEventQueue<EventType>()->AddListener(pEventListener);
		}
	
		template <typename EventType>
		void RemoveListener(EventListener<EventType>* pEventListener)
		{
			GetEventQueue<EventType>()->RemoveListener(pEventListener);
		}
	
		template <typename EventType>
		EventQueue<EventType>* GetEventQueue()
		{
			static_assert(std::is_base_of<BaseEvent, EventType>::value, "EventType should be derived from dae::BaseEvent");
	
			//search for the queue using std::type_index of the queues in the unordered_map
			auto queue = m_pvEventQueues.find(typeid(EventQueue<EventType>));
	
			//check if the queue was found
			if (queue == m_pvEventQueues.end())
			{
				//queue was not found in the existing queues so check if it is waiting to be added
				queue = m_pvNewEventQueues.find(typeid(EventQueue<EventType>));
	
				//check if the queue was found
				if (queue == m_pvNewEventQueues.end())
				{
					//queue was not found so create a new one and return it
					auto newEventQueue{ std::make_unique<EventQueue<EventType>>() };
					auto pNewEventQueue{ newEventQueue.get() };
					m_pvNewEventQueues[typeid(EventQueue<EventType>)] = std::unique_ptr<EventQueue<BaseEvent>>(reinterpret_cast<EventQueue<BaseEvent>*>(newEventQueue.get()));
					return pNewEventQueue;
				}
	
				//queue was found in the queues waiting to be added to the rest of the queues so return it
				return reinterpret_cast<EventQueue<EventType>*>(queue->second.get());
			}
	
			//queue was found so return it
			return reinterpret_cast<EventQueue<EventType>*>(queue->second.get());
		}
	
		void HandleEventQueues();
	
	private:
		std::unordered_map<std::type_index, std::unique_ptr<EventQueue<BaseEvent>>> m_pvEventQueues;
		std::unordered_map<std::type_index, std::unique_ptr<EventQueue<BaseEvent>>> m_pvNewEventQueues;
		bool m_EventWasAdded{};
	};
}