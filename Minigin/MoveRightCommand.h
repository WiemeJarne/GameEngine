#pragma once
#include "Command.h"
#include "Transform.h"

namespace commands
{
	class MoveRightCommand final : public Command
	{
	public:
		MoveRightCommand(dae::GameObject* go, float moveSpeed);

		virtual ~MoveRightCommand() = default;
		MoveRightCommand(const MoveRightCommand&) = delete;
		MoveRightCommand(MoveRightCommand&&) = delete;
		MoveRightCommand& operator=(const MoveRightCommand&) = delete;
		MoveRightCommand& operator=(MoveRightCommand&&) = delete;

		void Execute() override;
		void Undo() override;

	private:
		glm::vec3 m_PreviousLocalPos{};
		const float m_MoveSpeed{};
	};
}