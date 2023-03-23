#include "PlayerController.h"
#define KEY_DOWN_MASK 0x80

PlayerController::PlayerController(int controllerIndex)
	: m_ControllerIndex{ controllerIndex }
{}

void PlayerController::Update()
{
	HandleControllerInput();
	HandleKeyboardInput();
}

bool PlayerController::IsDownThisFrame(ControllerKey button) const
{
	return m_ButtonsPressedThisFrame & static_cast<unsigned int>(button);
}

bool PlayerController::IsUpThisFrame(ControllerKey button) const
{
	return m_ButtonsReleasedThisFrame & static_cast<unsigned int>(button);
}

bool PlayerController::IsPressed(ControllerKey button) const
{
	return m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button);
}

bool PlayerController::IsDownThisFrame(int button) const
{
	return (m_CurrentKeyboardKeysState[button] & KEY_DOWN_MASK) && !(m_PreviousKeyboardKeysState[button] & KEY_DOWN_MASK);
}

bool PlayerController::IsUpThisFrame(int button) const
{
	return !(m_CurrentKeyboardKeysState[button] & KEY_DOWN_MASK) && (m_PreviousKeyboardKeysState[button] & KEY_DOWN_MASK);
}

bool PlayerController::IsPressed(int button) const
{
	return (m_CurrentKeyboardKeysState[button] & KEY_DOWN_MASK);
}

void PlayerController::AddCommand(std::unique_ptr<commands::Command> command, Control controllerKey)
{
	m_ControllerCommands.insert(std::pair<Control, std::unique_ptr<commands::Command>>(controllerKey, std::move(command)));
}

void PlayerController::AddCommand(std::unique_ptr<commands::Command> command, KeyboardKey keyboardKey)
{
	m_KeyboardCommands.insert(std::pair<KeyboardKey, std::unique_ptr<commands::Command>>(keyboardKey, std::move(command)));
}

void PlayerController::HandleControllerInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

	for (const auto& command : m_ControllerCommands)
	{
		switch (command.first.first) //check what state the button should be for the command to be executed
		{
		case KeyState::down:
			//check if the button is down in the current frame if so execute the command
			if (IsDownThisFrame(command.first.second))
			{
				command.second->Execute();
			}
			break;

		case KeyState::up:
			//check if the button is up in the current frame if so execute the command
			if (IsUpThisFrame(command.first.second))
			{
				command.second->Execute();
			}
			break;

		case KeyState::pressed:
			//check if the button is pressed if so execute the command
			if (IsPressed(command.first.second))
			{
				command.second->Execute();
			}
			break;
		}
	}
}

void PlayerController::HandleKeyboardInput()
{
	memcpy(m_PreviousKeyboardKeysState, m_CurrentKeyboardKeysState, sizeof(m_PreviousKeyboardKeysState));
	GetKeyboardState(m_CurrentKeyboardKeysState);

	for (const auto& command : m_KeyboardCommands)
	{
		switch (command.first.first) //check what state the button should be for the command to be executed
		{
		case KeyState::down:
			//check if the button is down in the current frame if so execute the command
			if (IsDownThisFrame(command.first.second))
			{
				command.second->Execute();
			}
			break;

		case KeyState::up:
			//check if the button is up in the current frame if so execute the command
			if (IsUpThisFrame(command.first.second))
			{
				command.second->Execute();
			}
			break;

		case KeyState::pressed:
			//check if the button is pressed if so execute the command
			if (IsPressed(command.first.second))
			{
				command.second->Execute();
			}
			break;
		}
	}
}