#include "PointsCommand.h"
#include <iostream>

namespace commands
{
	PointsCommmand::PointsCommmand(dae::GameObject* go, int amountOfPointsToAddPerExecution)
		: m_AmountOfPointsToAdd{ amountOfPointsToAddPerExecution }
	{
		m_PointsComponent = go->GetComponent<PointsComponent>();
	}

	void PointsCommmand::Execute()
	{
		if (m_PointsComponent)
			m_PointsComponent->AddPoints(m_AmountOfPointsToAdd);
	}
}