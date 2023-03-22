#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	for (auto& controller : m_Controllers)
	{
		controller->Update();
	}

	return true;
}

void dae::InputManager::AddController(std::unique_ptr<PlayerController> playerController)
{
	m_Controllers.push_back(std::move(playerController));
}