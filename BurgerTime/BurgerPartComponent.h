#pragma once
#include "Component.h"
#include "LevelGrid.h"
#include "GameObject.h"
#include "EventListener.h"
#include <glm/vec2.hpp>
#include <any>

class BurgerPartComponent : public Component, public dae::EventListener
{
public:
	BurgerPartComponent(dae::GameObject* owner, float fallSpeed);
	~BurgerPartComponent();
	BurgerPartComponent(const BurgerPartComponent& other) = delete;
	BurgerPartComponent(BurgerPartComponent&& other) = delete;
	BurgerPartComponent& operator=(const BurgerPartComponent& other) = delete;
	BurgerPartComponent& operator=(BurgerPartComponent&& other) = delete;

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}
	bool GetIsFalling() const { return m_IsFalling; }
	bool GetHasReachedPlate() const { return m_HasReachedPlate; }
	const glm::vec2& GetTopLeftPos() const { return m_pOwner->GetLocalPos(); }
	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; }
	void SetHasReachedPlate(bool hasReachedPlate) { m_HasReachedPlate = hasReachedPlate; }
	void SetIsFalling(bool startFalling) { m_IsFalling = startFalling; }
	void OnNotify(std::any data, int eventId, bool isEngineEvent) override;

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
	bool m_IsFalling{};
	float m_ToGoYValue{};
	bool m_HasReachedPlate{};
	int m_AmountOfLevelsDropped{};

	void CalculateWalkedOver(dae::GameObject* pGameObject);
	void CollidedWithOtherBurgerPart(dae::GameObject* pGameObject);
	void HandleChildren(int childCount);
};