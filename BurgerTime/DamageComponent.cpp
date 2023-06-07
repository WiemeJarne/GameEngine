#include "DamageComponent.h"

DamageComponent::DamageComponent(dae::GameObject* pOwner, int damageAmount)
	: Component(pOwner)
	, m_DamageAmount{ damageAmount }
{}