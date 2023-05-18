#include "EventQueue.h"

void dae::EventQueue::Update()
{
	if (!m_Isinitialized)
	{
		m_pEvents.resize(m_Size);
	}

	std::tuple<std::any, int, bool> event;
	while (PollEvent(event))
	{
		for (auto pListener : m_Listeners)
		{
			pListener->OnNotify(std::get<0>(event), std::get<1>(event), std::get<2>(event));
		}
	}
}

void dae::EventQueue::AddListener(EventListener* pObserver)
{
	m_Listeners.push_back(pObserver);
}

void dae::EventQueue::RemoveListener(EventListener* pObserver)
{
	m_Listeners.erase(std::remove_if(m_Listeners.begin(), m_Listeners.end(), [&](EventListener* pOtherObserver) {return pObserver == pOtherObserver; }), m_Listeners.end());
}

bool dae::EventQueue::PollEvent(std::tuple<std::any, int, bool>& event)
{
	if (m_Head == m_Tail)
		return false;

	event = m_pEvents[m_Head];
	++m_Head;

	return true;
}