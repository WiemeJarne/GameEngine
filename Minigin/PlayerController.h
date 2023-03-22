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

	void Update();
	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;
	using ControllerKey = std::pair<KeyState, unsigned>;
	void AddCommand(std::unique_ptr<commands::Command> command, ControllerKey controllerKey);

private:
	XINPUT_STATE m_PreviousState;
	XINPUT_STATE m_CurrentState;
	const int m_ControllerIndex{};
	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};
	using CommandsMap = std::map<ControllerKey, std::unique_ptr<commands::Command>>;
	CommandsMap m_Commands;
};