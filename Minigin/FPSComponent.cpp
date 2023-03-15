#include "FPSComponent.h"
#include "Timer.h"
#include "TextComponent.h"

FPSComponent::FPSComponent(dae::GameObject* owner, std::shared_ptr<dae::TextComponent> textComponent)
	: Component(owner),
	  m_TextComponent{ textComponent }
{}

FPSComponent::~FPSComponent() = default;

void FPSComponent::Update()
{
	m_Timer += Timer::GetInstance().GetElapsedSec();

	m_FPS = 1.f / Timer::GetInstance().GetElapsedSec();

	if (m_Timer >= 1.f) //update the text 1 time per second
	{
		m_Timer = 0.f;
		m_TextComponent->SetText(std::to_string(static_cast<int>(m_FPS)) + " FPS");
	}
}