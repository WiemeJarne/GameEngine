#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"
#include <Windows.h>

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONUP) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				for (auto& button : m_pButtons)
				{
					button->OnMouseClick(glm::vec2(static_cast<float>(e.button.x), static_cast<float>(e.button.y)));
				}
			}
		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	for (auto& controller : m_Controllers)
	{
		controller->Update();
	}

	HandleKeyboardInput();

	return true;
}

void dae::InputManager::AddController(std::unique_ptr<PlayerController> playerController)
{
	m_Controllers.push_back(std::move(playerController));
}

void dae::InputManager::AddCommand(std::unique_ptr<commands::Command> command, KeyboardKey keyboardKey)
{
	m_KeyboardCommands.insert(std::pair<KeyboardKey, std::unique_ptr<commands::Command>>(keyboardKey, std::move(command)));
}

void dae::InputManager::AddButton(ButtonComponent* pButtomComponent)
{
	m_pButtons.push_back(pButtomComponent);
}

void dae::InputManager::HandleKeyboardInput()
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

bool dae::InputManager::IsDownThisFrame(int button) const
{
	return (m_CurrentKeyboardKeysState[button] & KEY_DOWN_MASK) && !(m_PreviousKeyboardKeysState[button] & KEY_DOWN_MASK);
}

bool dae::InputManager::IsUpThisFrame(int button) const
{
	return !(m_CurrentKeyboardKeysState[button] & KEY_DOWN_MASK) && (m_PreviousKeyboardKeysState[button] & KEY_DOWN_MASK);
}

bool dae::InputManager::IsPressed(int button) const
{
	return (m_CurrentKeyboardKeysState[button] & KEY_DOWN_MASK);
}