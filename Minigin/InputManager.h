#pragma once
#include "Singleton.h"
#include <vector>
#include "PlayerController.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddController(std::unique_ptr<PlayerController> playerController);
		int GetAmountOfPlayers() const { return static_cast<int>(m_Controllers.size()); }

	private:
		std::vector<std::unique_ptr<PlayerController>> m_Controllers{};
	};

}