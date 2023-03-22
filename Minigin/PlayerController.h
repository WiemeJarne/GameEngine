#pragma once
#include <memory>
#include <vector>
#include <tuple>
#include <windows.h>
#include <XInput.h>
#include "Command.h"

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
	void AddCommand(unsigned int button, KeyState keyState, std::function<void()> command);

private:
	XINPUT_STATE m_PreviousState;
	XINPUT_STATE m_CurrentState;
	const int m_ControllerIndex{};
	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};
	std::vector<std::tuple<unsigned int, KeyState, std::function<void()>>> m_Commands;
};