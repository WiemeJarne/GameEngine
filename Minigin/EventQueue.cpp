#include "EventQueue.h"

void dae::EventQueue::Update()
{
	if (!m_Isinitialized)
	{
		m_pEvents.resize(m_Size);
	}

	std::unique_ptr<std::tuple<std::any, int, bool>> e;
	while (m_Head != m_Tail)
	{
		e = std::move(m_pEvents[m_Head]);

		if (e == nullptr)
			return;

		for (auto pListener : m_Listeners)
		{
			if(pListener)
				pListener->OnNotify(std::get<0>(*e), std::get<1>(*e), std::get<2>(*e));
		}

		m_pEvents[m_Head] = nullptr;
		m_Head = (m_Head + 1) % m_Size;
	}

	if (!m_Listeners.empty())
		m_Listeners.erase(std::remove_if(m_Listeners.begin(), m_Listeners.end(), [&](EventListener* pObserver) {return pObserver == nullptr; }), m_Listeners.end());
}

void dae::EventQueue::AddListener(EventListener* pObserver)
{
	m_Listeners.push_back(pObserver);
}

void dae::EventQueue::RemoveListener(EventListener* pObserver)
{
	for (auto& listener : m_Listeners)
	{
		if (listener == pObserver)
			listener = nullptr;
	}
}

void dae::EventQueue::AddEvent(std::any pData, int eventId, bool isEngineEvent)
{
	if ((m_Tail + 1) % m_Size == m_Head)
	{
		m_Size += m_Size / 2;
		m_pEvents.resize(m_Size);
	}

	m_pEvents[m_Tail] = std::move(std::make_unique<std::tuple<std::any, int, bool>>(pData, eventId, isEngineEvent));
	m_Tail = (m_Tail + 1) % m_Size;
}