#pragma once
#include "Command.h"
#include "Transform.h"

namespace commands
{
	class MoveDownCommand final : public Command
	{
	public:
		MoveDownCommand(dae::GameObject* go, float moveSpeed);

		virtual ~MoveDownCommand() = default;
		MoveDownCommand(const MoveDownCommand&) = delete;
		MoveDownCommand(MoveDownCommand&&) = delete;
		MoveDownCommand& operator=(const MoveDownCommand&) = delete;
		MoveDownCommand& operator=(MoveDownCommand&&) = delete;

		void Execute() override;
		void Undo() override;

	private:
		glm::vec3 m_PreviousLocalPos{};
		const float m_MoveSpeed{};
	};
}