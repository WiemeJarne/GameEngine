#pragma once
#include <memory>
#include <vector>
#include <tuple>
#include <windows.h>
#include <XInput.h>
#include "Command.h"
#include <map>

class PlayerController final
{
public:
	PlayerController(int controllerIndex);
	~PlayerController() = default;

	enum class KeyState
	{
		down,
		up,
		pressed
	};

	enum class ControllerKey : unsigned int
	{
		dPadUp = XINPUT_GAMEPAD_DPAD_UP,
		dPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		dPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		dPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		start = XINPUT_GAMEPAD_START,
		back = XINPUT_GAMEPAD_BACK,
		tumbStickLeft = XINPUT_GAMEPAD_LEFT_THUMB,
		tumbStickRight = XINPUT_GAMEPAD_RIGHT_THUMB,
		shoulderLeft = XINPUT_GAMEPAD_LEFT_SHOULDER,
		shoulderRight = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		a = XINPUT_GAMEPAD_A,
		b = XINPUT_GAMEPAD_B,
		x = XINPUT_GAMEPAD_X,
		y = XINPUT_GAMEPAD_Y
	};

	void Update();
	bool IsDownThisFrame(ControllerKey button) const;
	bool IsUpThisFrame(ControllerKey button) const;
	bool IsPressed(ControllerKey button) const;
	bool IsDownThisFrame(int button) const;
	bool IsUpThisFrame(int button) const;
	bool IsPressed(int button) const;
	using Control = std::pair<KeyState, ControllerKey>;
	void AddCommand(std::unique_ptr<commands::Command> command, Control controllerKey);
	using KeyboardKey = std::pair<KeyState, int>;
	void AddCommand(std::unique_ptr<commands::Command> command, KeyboardKey keyboardKey);

private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	const int m_ControllerIndex{};
	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};
	using ControllerCommandsMap = std::map<Control, std::unique_ptr<commands::Command>>;
	ControllerCommandsMap m_ControllerCommands{};
	using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<commands::Command>>;
	KeyboardCommandsMap m_KeyboardCommands{};
	BYTE m_CurrentKeyboardKeysState[256]{};
	BYTE m_PreviousKeyboardKeysState[256]{};

	void HandleControllerInput();
	void HandleKeyboardInput();
};