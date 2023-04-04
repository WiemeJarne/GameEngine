#include "MoveCommand.h"
#include "Timer.h"
#include <iostream>

using namespace commands;

MoveCommand::MoveCommand(dae::GameObject* go, glm::vec2 moveDirection, float moveSpeed)
	: m_Go{ go }
	, m_MoveDirection{ moveDirection }
	, m_MoveSpeed{ moveSpeed }
{}

void MoveCommand::Execute()
{
	m_Go->SetLocalPosition(m_Go->GetLocalPos().x + Timer::GetInstance().GetElapsedSec() * m_MoveSpeed * m_MoveDirection.x,
						   m_Go->GetLocalPos().y + Timer::GetInstance().GetElapsedSec() * m_MoveSpeed * m_MoveDirection.y);
}