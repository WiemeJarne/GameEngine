#pragma once
#include "Component.h"

class MoveInCircleComponent final : public Component
{
public:
	MoveInCircleComponent(std::weak_ptr<dae::GameObject> owner, float radius, float angularSpeed, bool clockWise = true);
	~MoveInCircleComponent() = default;

	void Update() override;
	void Render() const override {}

private:
	const float m_Radius;
	const float m_AngularSpeed;
	float m_CurrentAngle;
	const bool m_ClockWise;
	bool m_IsInitialised;
};

