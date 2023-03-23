#include "MoveUpCommand.h"
#include "Timer.h"
#include <iostream>

using namespace commands;

MoveUpCommand::MoveUpCommand(dae::GameObject* go, float moveSpeed)
	: Command(go)
	, m_MoveSpeed{ moveSpeed }
{
	m_PreviousLocalPos = go->GetLocalPos();
}

void MoveUpCommand::Execute()
{
	auto go{ GetGameObject() };
	m_PreviousLocalPos = go->GetLocalPos();
	glm::vec3 newPos{ m_PreviousLocalPos };
	newPos.y = m_PreviousLocalPos.y - Timer::GetInstance().GetElapsedSec() * m_MoveSpeed;
	go->SetLocalPosition(newPos.x, newPos.y);
}

void MoveUpCommand::Undo()
{
	auto go{ GetGameObject() };
	go->SetLocalPosition(m_PreviousLocalPos.x, m_PreviousLocalPos.y);
}