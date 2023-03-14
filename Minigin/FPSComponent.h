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
	FPSComponent(dae::GameObject* owner, std::shared_ptr<dae::TextComponent> textComponent);
	~FPSComponent();
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	virtual void Update() override;
	virtual void Render() const override {};

private:
	float m_FPS{ 0.f };
	float m_Timer{ 0.f };
	std::chrono::high_resolution_clock::time_point m_PreviousTime;
	std::shared_ptr<dae::TextComponent> m_TextComponent;
};