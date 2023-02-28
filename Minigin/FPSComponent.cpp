#include "FPSComponent.h"
#include "Timer.h"
#include "TextComponent.h"

FPSComponent::FPSComponent(std::shared_ptr<dae::TextComponent> textComponent)
	: m_TextComponent{ textComponent }
{

}

FPSComponent::~FPSComponent() = default;

void FPSComponent::Update()
{
	m_FPSTimer += Timer::GetInstance().GetElapsedSec();
	++m_FrameCount;

	if (m_FPSTimer >= 1.f)
	{
		m_FPS = m_FrameCount;
		m_FPSTimer = 0.f;
		m_FrameCount = 0;
		m_TextComponent->SetText(std::to_string(m_FPS) + " FPS");
	}
}