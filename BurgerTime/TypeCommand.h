#pragma once
#include "Command.h"
#include "TextComponent.h"

namespace commands
{
	class TypeCommand final : public Command
	{
	public:
		TypeCommand(char charToType, dae::TextComponent* textComponentToTypeTo); //use /b for backspace

		void Execute();
		
	private:
		char m_CharToType;
		dae::TextComponent* m_pTextComponentToTypeTo;
		dae::GameObject* m_pTextComponentOwner;

		void RecenterAlongXAxis();
	};
}