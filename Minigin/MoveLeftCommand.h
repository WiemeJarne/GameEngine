#pragma once
#include "Command.h"
#include "Transform.h"

namespace commands
{
	class MoveLeftCommand final : public Command
	{
	public:
		MoveLeftCommand(dae::GameObject* go, float moveSpeed);

		virtual ~MoveLeftCommand() = default;
		MoveLeftCommand(const MoveLeftCommand&) = delete;
		MoveLeftCommand(MoveLeftCommand&&) = delete;
		MoveLeftCommand& operator=(const MoveLeftCommand&) = delete;
		MoveLeftCommand& operator=(MoveLeftCommand&&) = delete;

		void Execute() override;
		void Undo() override;

	private:
		glm::vec3 m_PreviousLocalPos{};
		const float m_MoveSpeed{};
	};
}