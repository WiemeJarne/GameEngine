#include "PlayerController.h"
#include "SDL.h"
#include <iostream>

PlayerController::PlayerController(int controllerIndex)
	: m_ControllerIndex{ controllerIndex }
{}

void PlayerController::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	for (const auto& command : m_Commands)
	{
		switch (std::get<1>(command)) //check what state the button should be for the command to be executed
		{
			case KeyState::down:
				//check if the button is down in the current frame if so execute the command
				if (IsDownThisFrame(std::get<0>(command))) 
				{
					std::get<2>(command)();
				}
				break;

			case KeyState::up:
				//check if the button is up in the current frame if so execute the command
				if (IsUpThisFrame(std::get<0>(command)))
				{
					std::get<2>(command)();
				}
				break;

			case KeyState::pressed:
				//check if the button is pressed if so execute the command
				if (IsPressed(std::get<0>(command)))
				{
					std::get<2>(command)();
				}
				break;
		}
	}

	auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool PlayerController::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool PlayerController::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

bool PlayerController::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

void PlayerController::AddCommand(unsigned int button, KeyState keyState, std::function<void()> command)
{
	m_Commands.push_back(std::make_tuple(button, keyState, command));
}