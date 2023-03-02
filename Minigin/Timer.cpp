#include "Timer.h"
#include <iostream>

void Timer::Start()
{
	m_BeginTime = std::chrono::high_resolution_clock::now();
	m_PreviousTime = m_BeginTime;
}

void Timer::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_ElapsedSec = std::chrono::duration<float>(currentTime - m_PreviousTime).count();
	m_PreviousTime = currentTime;
	
	m_TotalSec += m_ElapsedSec;
}