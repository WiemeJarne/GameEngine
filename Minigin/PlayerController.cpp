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

	auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

	for (const auto& command : m_Commands)
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

void PlayerController::AddCommand(std::unique_ptr<commands::Command> command, ControllerKey controllerKey)
{
	m_Commands.insert(std::pair<ControllerKey, std::unique_ptr<commands::Command>>(controllerKey, std::move(command)));
}