#pragma once
#include "Singleton.h"
#include <vector>
#include "PlayerController.h"
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
		void AddController(std::unique_ptr<PlayerController> playerController);
		int GetAmountOfControllers() const { return static_cast<int>(m_Controllers.size()); }

		using KeyboardKey = std::pair<KeyState, int>;
		void AddCommand(std::unique_ptr<commands::Command> command, KeyboardKey keyboardKey);

	private:
		std::vector<std::unique_ptr<PlayerController>> m_Controllers{};
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<commands::Command>>;
		KeyboardCommandsMap m_KeyboardCommands{};
		uint8_t m_CurrentKeyboardKeysState[256]{};
		uint8_t m_PreviousKeyboardKeysState[256]{};

		void HandleKeyboardInput();
		bool IsDownThisFrame(int button) const;
		bool IsUpThisFrame(int button) const;
		bool IsPressed(int button) const;
	};
}