#include "PlayerController.h"
#include <Windows.h>
#include <XInput.h>
#include "InputManager.h"

class PlayerController::PlayerControllerImpl final
{
public:
	PlayerControllerImpl(int controllerIndex)
	{
		if (controllerIndex == -1)
		{
			m_ControllerIndex = dae::InputManager::GetInstance().GetAmountOfControllers();
		}
		else
		{
			m_ControllerIndex = controllerIndex;
		}
	}

	~PlayerControllerImpl() = default;
	PlayerControllerImpl(const PlayerControllerImpl& other) = delete;
	PlayerControllerImpl(PlayerControllerImpl&& other) = default;
	PlayerControllerImpl& operator=(const PlayerControllerImpl& other) = delete;
	PlayerControllerImpl& operator=(PlayerControllerImpl&& other) = delete;

	void HandleControllerInput()
	{
		if (m_ControllerIndex < 0)
			return;

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
			case dae::KeyState::down:
				//check if the button is down in the current frame if so execute the command
				if (IsDownThisFrame(command.first.second))
				{
					command.second->Execute();
				}
				break;

			case dae::KeyState::up:
				//check if the button is up in the current frame if so execute the command
				if (IsUpThisFrame(command.first.second))
				{
					command.second->Execute();
				}
				break;

			case dae::KeyState::pressed:
				//check if the button is pressed if so execute the command
				if (IsPressed(command.first.second))
				{
					command.second->Execute();
				}
				break;
			}
		}
	}

	void AddCommand(std::unique_ptr<commands::Command> command, Control controllerKey)
	{
		m_ControllerCommands.insert(std::pair<Control, std::unique_ptr<commands::Command>>(controllerKey, std::move(command)));
	}

private:

	bool IsDownThisFrame(ControllerKey button) const
	{
		return m_ButtonsPressedThisFrame & static_cast<unsigned int>(button);
	}

	bool IsUpThisFrame(ControllerKey button) const
	{
		return m_ButtonsReleasedThisFrame & static_cast<unsigned int>(button);
	}

	bool IsPressed(ControllerKey button) const
	{
		return m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button);
	}

	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	int m_ControllerIndex{};
	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};
	using ControllerCommandsMap = std::map<Control, std::unique_ptr<commands::Command>>;
	ControllerCommandsMap m_ControllerCommands{};
};

PlayerController::PlayerController()
	: m_PlayerControllerImpl{ std::make_unique<PlayerControllerImpl>(-1) } //when the playerController is created for keyboard input then the controller index is set to -1
{}

PlayerController::PlayerController(int controllerIndex)
	: m_PlayerControllerImpl{ std::make_unique<PlayerControllerImpl>(controllerIndex) }
{}

PlayerController::~PlayerController() = default;

void PlayerController::Update()
{
	m_PlayerControllerImpl->HandleControllerInput();
}

void PlayerController::AddCommand(std::unique_ptr<commands::Command> command, Control controllerKey)
{
	m_PlayerControllerImpl->AddCommand(std::move(command), controllerKey);
}