#pragma once
#include "Component.h"
#include "LevelGrid.h"
#include "Observer.h"
#include "GameObject.h"
#include <glm/vec2.hpp>

class BurgerPartComponent : public Component, public Observer<dae::GameObject>
{
public:
	BurgerPartComponent(dae::GameObject* owner, float fallSpeed);
	~BurgerPartComponent() = default;
	BurgerPartComponent(const BurgerPartComponent& other) = delete;
	BurgerPartComponent(BurgerPartComponent&& other) = delete;
	BurgerPartComponent& operator=(const BurgerPartComponent& other) = delete;
	BurgerPartComponent& operator=(BurgerPartComponent&& other) = delete;

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}
	void OnNotify(dae::GameObject* go, int eventId) override;
	bool GetHasReachedPlate() const { return m_HasReachedPlate; }
	const glm::vec2& GetTopLeftPos() const { return m_pOwner->GetLocalPos(); }
	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }
	void SetHasReachedPlate(bool hasReachedPlate) { m_HasReachedPlate = hasReachedPlate; }
	void SetStartFalling(bool startFalling) { m_StartFalling = startFalling; }

private:
	float m_Width{};
	float m_Height{};
	const float m_FallSpeed{};
	Cell* m_pCell{};
	Cell* m_pPreviousCell{};
	bool m_FirstQuarterWalkedOver{};
	bool m_SecondWalkedOver{};
	bool m_ThirdWalkedOver{};
	bool m_FourthWalkedOver{};
	bool m_ShouldFallUntilPlatform{};
	bool m_StartFalling{};
	float m_ToGoYValue{};
	bool m_HasReachedPlate{};
};