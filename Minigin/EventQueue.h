#pragma once
#include "Singleton.h"
#include <vector>
#include "EventListener.h"
#include <tuple>
#include <any>
#include <memory>

namespace dae
{
	class EventQueue final : public Singleton<EventQueue>
	{
	public:
		EventQueue() = default;

		void Update();
		void AddListener(EventListener* pObserver);
		void RemoveListener(EventListener* pObserver);
		void AddEvent(std::any pData, int eventId, bool isEngineEvent);

	private:
		std::vector<EventListener*> m_Listeners{};
		std::vector <std::unique_ptr<std::tuple<std::any, int, bool>>> m_pEvents{};
		bool m_Isinitialized{};
		int m_Head{};
		int m_Tail{};
		int m_Size{ 10 };
	};
}