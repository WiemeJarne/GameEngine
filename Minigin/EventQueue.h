#pragma once
#include "Singleton.h"
#include <vector>
#include "EventListener.h"
#include <tuple>
#include <any>

namespace dae
{
	class EventQueue final : public Singleton<EventQueue>
	{
	public:
		EventQueue() = default;

		void Update();
		void AddListener(EventListener* pObserver);
		void RemoveListener(EventListener* pObserver);

		//template<typename T>
		/*void AddEvent(T* pData, int eventId, bool isEngineEvent)
		{
			if (m_Tail >= (m_Size - 1))
			{
				m_Size += m_Size / 2;
				m_pEvents.resize(m_Size);
			}

			m_pEvents[m_Tail] = std::tuple<void*, int, bool>(pData, eventId, isEngineEvent);
			++m_Tail;
		}*/

		void AddEvent(std::any pData, int eventId, bool isEngineEvent)
		{
			if (m_Tail >= (m_Size - 1))
			{
				m_Size += m_Size / 2;
				m_pEvents.resize(m_Size);
			}

			m_pEvents[m_Tail] = std::tuple<std::any, int, bool>(pData, eventId, isEngineEvent);
			++m_Tail;
		}

	private:
		std::vector<EventListener*> m_Listeners{};
		std::vector <std::tuple<std::any, int, bool>> m_pEvents{};
		bool m_Isinitialized{};
		int m_Head{};
		int m_Tail{};
		int m_Size{ 10 };

		bool PollEvent(std::tuple<std::any, int, bool>& event);
	};
}