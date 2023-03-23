#pragma once
#include <memory>
#include "Command.h"
#include <windows.h>
#include <map>

class PlayerController final
{
public:
	PlayerController(int controllerIndex);
	~PlayerController();
	PlayerController(const PlayerController& other) = delete;
	PlayerController(PlayerController&& other) = default;
	PlayerController& operator=(const PlayerController& other) = delete;
	PlayerController& operator=(PlayerController&& other) = delete;

	enum class KeyState
	{
		down,
		up,
		pressed
	};

	enum class ControllerKey : unsigned int
	{
		dPadUp = 0x0001,
		dPadDown = 0x0002,
		dPadLeft = 0x0004,
		dPadRight = 0x0008,
		start = 0x0010,
		back = 0x0020,
		tumbStickLeft = 0x0040,
		tumbStickRight = 0x0080,
		shoulderLeft = 0x0100,
		shoulderRight = 0x0200,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000
	};

	void Update();
	
	using Control = std::pair<KeyState, ControllerKey>;
	void AddCommand(std::unique_ptr<commands::Command> command, Control controllerKey);
	using KeyboardKey = std::pair<KeyState, int>;
	void AddCommand(std::unique_ptr<commands::Command> command, KeyboardKey keyboardKey);

private:
	using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<commands::Command>>;
	KeyboardCommandsMap m_KeyboardCommands{};
	BYTE m_CurrentKeyboardKeysState[256]{};
	BYTE m_PreviousKeyboardKeysState[256]{};

	class PlayerControllerImpl;
	std::unique_ptr<PlayerControllerImpl> m_PlayerControllerImpl;

	void HandleKeyboardInput();
	bool IsDownThisFrame(int button) const;
	bool IsUpThisFrame(int button) const;
	bool IsPressed(int button) const;
};