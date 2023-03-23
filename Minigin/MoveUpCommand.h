#pragma once
#include "Command.h"
#include "Transform.h"

namespace commands
{
	class MoveUpCommand final : public Command
	{
	public:
		MoveUpCommand(dae::GameObject* go, float moveSpeed);

		virtual ~MoveUpCommand() = default;
		MoveUpCommand(const MoveUpCommand&) = delete;
		MoveUpCommand(MoveUpCommand&&) = delete;
		MoveUpCommand& operator=(const MoveUpCommand&) = delete;
		MoveUpCommand& operator=(MoveUpCommand&&) = delete;

		void Execute() override;
		void Undo() override;

	private:
		glm::vec3 m_PreviousLocalPos{};
		const float m_MoveSpeed{};
	};
}