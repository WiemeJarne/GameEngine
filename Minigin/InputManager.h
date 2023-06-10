#pragma once
#include "Singleton.h"
#include <vector>
#include "PlayerController.h"
#include "ButtonComponent.h"
#include <map>
#include <memory>
#define KEY_DOWN_MASK 0x80

namespace dae
{
	enum class KeyState
	{
		down,
		up,
		pressed
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddController(std::unique_ptr<dae::PlayerController> playerController);
		int GetAmountOfControllers() const { return static_cast<int>(m_Controllers.size()); }

		enum class KeyboardKey
		{
			A, B, C, D,
			E, F, G, H,
			I, J, K, L,
			M, N, O, P,
			Q, R, S, T,
			U, V, W, X,
			Y, Z,
			F1, F2, F3, F4,
			F5, F6, F7, F8,
			F9, F10, F11, F12,
			BackSpace,
			Minus,
			Space
		};
		
		void AddCommand(std::unique_ptr<dae::Command> command, KeyState keyState, KeyboardKey keyboardKey);
		void AddButton(ButtonComponent* pButtomComponent);
		void RemoveAllButtons();
		void RemoveAllCommandsAndControlers();

	private:
		std::vector<std::unique_ptr<dae::PlayerController>> m_Controllers;
		using KeyboardAction = std::pair<KeyState, int>;
		using KeyboardCommandsMap = std::map<KeyboardAction, std::unique_ptr<dae::Command>>;
		KeyboardCommandsMap m_KeyboardCommands;
		uint8_t m_CurrentKeyboardKeysState[256]{};
		uint8_t m_PreviousKeyboardKeysState[256]{};
		std::vector<ButtonComponent*> m_pButtons{};
		bool m_CommandsWhereRemoved{};

		void HandleKeyboardInput();
		bool IsDownThisFrame(int button) const;
		bool IsUpThisFrame(int button) const;
		bool IsPressed(int button) const;
		int ConvertKeyboardKeyToInt(KeyboardKey keyboardKey) const;
	};
}