#include "StunnedState.h"
#include  "NotStunnedState.h"
#include "Timer.h"

StunnedState::StunnedState(DamageComponent* pDamageComponent, HealthComponent* pHealthComponent, EnemyAIComponent* pEnemyAIComponent)
	: m_pDamageComponent{ pDamageComponent }
	, m_pHealthComponent{ pHealthComponent }
	, m_pEnemyAIComponent{ pEnemyAIComponent }
{}

EnemyState* StunnedState::Update()
{
	m_SecSinceStunned += dae::Timer::GetInstance().GetElapsedSec();

	//check if the enemy should stop being stunned
	if (m_SecSinceStunned >= m_pHealthComponent->GetAmountOfSecStunned() || !m_pHealthComponent->GetIsCollidingWithPepper() || (m_pEnemyAIComponent->GetIsFallingWithBurgerPart() && !m_pEnemyAIComponent->GetOwner()))
		return new NotStunnedState(m_pDamageComponent, m_pHealthComponent, m_pEnemyAIComponent);

	//if the enemy can't walk anymore return this (because the enemy is already stunned)
	if (!m_pEnemyAIComponent->GetCanMove())
		return this;

	//else make sure he can't do damage
	m_pDamageComponent->SetCanDoDamage(false);

	//make sure he can't move
	m_pEnemyAIComponent->SetCanMove(false);

	return this;
}