#pragma once
#include <chrono>
#include "Singleton.h"

class Timer final : public dae::Singleton<Timer>
{
public:
	void Start();
	void Update();

	int GetFPS() const { return m_FPS; }
	float GetTotalSec() const { return m_TotalSec; }
	float GetElapsedSec() const { return m_ElapsedSec; }

private:
	int m_FPS{ 0 };
	int m_FrameCount{ 0 };
	float m_FPSTimer{ 0.f };
	float m_TotalSec{ 0.f };
	float m_ElapsedSec{ 0.f };
	std::chrono::high_resolution_clock::time_point m_PreviousTime;
	std::chrono::high_resolution_clock::time_point m_BeginTime;
};