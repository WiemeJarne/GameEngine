#pragma once
#include <vector>
#include "EventListener.h"
#include <memory>

namespace dae
{
	template <typename EventType>
	class EventQueue final
	{
	public:
		EventQueue()
			: m_Head{ 0 }
			, m_Tail{ 0 }
			, m_Size{ 10 }
		{
			m_pEvents.resize(m_Size);
		}

		~EventQueue() = default;

		void Update()
		{
			std::unique_ptr<EventType> e;
			while (m_Head != m_Tail)
			{
				e = std::move(m_pEvents[m_Head]);

				if (e == nullptr)
					return;

				for (auto pListener : m_Listeners)
				{
					if (pListener)
						pListener->OnNotify(e.get());

					if (m_ListenerRemoved)
					{
						m_ListenerRemoved = false;
						break;
					}
				}

				m_pEvents[m_Head] = nullptr;
				m_Head = (m_Head + 1) % m_Size;
			}

			if (!m_Listeners.empty())
				m_Listeners.erase(std::remove_if(m_Listeners.begin(), m_Listeners.end(), [&](EventListener<EventType>* pObserver) {return pObserver == nullptr; }), m_Listeners.end() );
		}

		void AddListener(EventListener<EventType>* pEventListener)
		{
			m_Listeners.push_back(pEventListener);
		}

		void RemoveListener(EventListener<EventType>* pEventListener)
		{
			for (auto& listener : m_Listeners)
			{
				if (listener == pEventListener)
				{
					m_ListenerRemoved = true;
					listener = nullptr;
				}
			}
		}

		void AddEvent(std::unique_ptr<EventType> pEvent)
		{
			if ((m_Tail + 1) % m_Size == m_Head)
			{
				m_Size += m_Size / 2;
				m_pEvents.resize(m_Size);
			}

			m_pEvents[m_Tail] = std::move(pEvent);
			m_Tail = (m_Tail + 1) % m_Size;
		}

	private:
		std::vector<EventListener<EventType>*> m_Listeners{};
		std::vector<std::unique_ptr<EventType>> m_pEvents{};
		int m_Head{};
		int m_Tail{};
		int m_Size{};
		bool m_ListenerRemoved{};
	};
}