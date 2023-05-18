// BurgerTime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "Timer.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "MoveInCircleComponent.h"
#include "Renderer.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "MoveCommand.h"
#include "HealthComponent.h"
#include "DamageCommand.h"
#include "PointsCommand.h"
#include "LivesDisplayComponent.h"
#include "PointsDisplayComponent.h"
#include "PlayerPrefab.h"
#include <iostream>
#include <vector>
#include "PlatformPrefab.h"
#include "LevelManager.h"
#include "PlaySoundCommand.h"
#include "SDLSoundSystem.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	LevelManager::GetInstance().LoadLevel(3, scene);

	//std::cout << "controls: \n";
	//std::cout << "\tMr. hotdog:\n";
	//std::cout << "\t\t moving: dPad\n";
	//std::cout << "\t\t take damamge: right bumper\n";
	//std::cout << "\t\t gain a point: A\n";
	//std::cout << "\tPeter Pepper:\n";
	//std::cout << "\t\t moving: WASD\n";
	//std::cout << "\t\t take damamge: spacebar\n";
	//std::cout << "\t\t gain a point: p\n";
	//std::cout << "green text is for Mr hotdog and yellow text is for Peter Pepper\n";

	std::cout << "press P to play a sound\n";

	auto pSDLSoundSystem{ new dae::SDLSoundSystem() };
	pSDLSoundSystem->AddSound("../Data/sound/LoseLife.wav");
	auto playSoundCommand = std::make_unique<commands::PlaySoundCommand>(pSDLSoundSystem);

	dae::InputManager::GetInstance().AddCommand(std::move(playSoundCommand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'P'));
}

int main(int, char* []) {
	
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}