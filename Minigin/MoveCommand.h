#pragma once
#include "Command.h"
#include "Transform.h"

namespace commands
{
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(dae::GameObject* go, glm::vec2 moveDirection, float moveSpeed);

		virtual ~MoveCommand() = default;
		MoveCommand(const MoveCommand&) = delete;
		MoveCommand(MoveCommand&&) = delete;
		MoveCommand& operator=(const MoveCommand&) = delete;
		MoveCommand& operator=(MoveCommand&&) = delete;

		void Execute() override;

	private:
		dae::GameObject* m_Go;
		glm::vec2 m_MoveDirection{};
		const float m_MoveSpeed{};
	};
}