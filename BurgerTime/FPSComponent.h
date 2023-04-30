#pragma once
#include <chrono>
#include "Component.h"

namespace dae
{
	class TextComponent;
}

class FPSComponent final : public Component
{
public:
	FPSComponent(dae::GameObject* owner, dae::TextComponent* textComponent);
	~FPSComponent();
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}

private:
	float m_FPS{ 0.f };
	float m_Timer{ 0.f };
	std::chrono::high_resolution_clock::time_point m_PreviousTime;
	dae::TextComponent* m_TextComponent;
};