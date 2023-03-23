#pragma once
#include "GameObject.h"

namespace commands
{
	class Command
	{
	public:
		Command(dae::GameObject* go);

		virtual ~Command() = default;
		Command(const Command&) = delete;
		Command(Command&&) = default;
		Command& operator=(const Command&) = delete;
		Command& operator=(Command&&) = delete;

		virtual void Execute() = 0;
		virtual void Undo() = 0;

	protected:
		dae::GameObject* GetGameObject() const { return m_Go; }

	private:
		dae::GameObject* m_Go;
	};
}