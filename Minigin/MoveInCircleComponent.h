#pragma once
#include "Component.h"
#include <string>

class MoveInCircleComponent final : public Component
{
public:
	MoveInCircleComponent(dae::GameObject* owner, float radius, float angularSpeed, bool clockWise = true);
	~MoveInCircleComponent() = default;
	MoveInCircleComponent(const MoveInCircleComponent& other) = delete;
	MoveInCircleComponent(MoveInCircleComponent&& other) = delete;
	MoveInCircleComponent& operator=(const MoveInCircleComponent& other) = delete;
	MoveInCircleComponent& operator=(MoveInCircleComponent&& other) = delete;

	void Update() override;
	void Render() const override {}

private:
	const float m_Radius;
	const float m_AngularSpeed;
	float m_CurrentAngle;
	const bool m_ClockWise;
	bool m_IsInitialised;
};

