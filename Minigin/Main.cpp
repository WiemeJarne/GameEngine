#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
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
#include "TrashTheCacheComponent.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"
#include <iostream>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto renderComponent = std::make_unique<RenderComponent>(go.get(), "background.tga");
	go->AddComponent(std::move(renderComponent));
	scene.Add(std::move(go));
	
	go = std::make_shared<dae::GameObject>();
	renderComponent = std::make_unique<RenderComponent>(go.get(), "logo.tga");
	go->AddComponent(std::move(renderComponent));
	go->SetWorldPosition(216, 180);
	scene.Add(std::move(go));
	
	go = std::make_shared<dae::GameObject>();
	go->SetWorldPosition(80, 20);
	 renderComponent = std::make_unique<RenderComponent>(go.get());
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<dae::TextComponent>(go.get(), "Programming 4 Assignment", font, renderComponent.get());
	go->AddComponent(std::move(renderComponent));
	go->AddComponent(std::move(to));
	scene.Add(std::move(go));
	
	go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition(310.f, 300.f);
	renderComponent = std::make_unique<RenderComponent>(go.get(), "MrHotDog.png");
	go->AddComponent(std::move(renderComponent));
	float moveSpeed{ 50.f };
	//create moveLeftCommand
	auto moveLeftCommmand{ std::make_unique<commands::MoveLeftCommand>(go.get(), moveSpeed) };
	//create moveRightCommand
	auto moveRightCommmand{ std::make_unique<commands::MoveRightCommand>(go.get(), moveSpeed) };
	//create moveUpCommand
	auto moveUpCommmand{ std::make_unique<commands::MoveUpCommand>(go.get(), moveSpeed) };
	//create moveUpCommand
	auto moveDownCommmand{ std::make_unique<commands::MoveDownCommand>(go.get(), moveSpeed) };
	//creat playerController
	auto playerController{ std::make_unique<PlayerController>(0) };
	//add the commands to the player controller
	playerController->AddCommand(std::move(moveLeftCommmand), PlayerController::Control(PlayerController::KeyState::pressed, PlayerController::ControllerKey::dPadLeft));
	playerController->AddCommand(std::move(moveRightCommmand), PlayerController::Control(PlayerController::KeyState::pressed, PlayerController::ControllerKey::dPadRight));
	playerController->AddCommand(std::move(moveUpCommmand), PlayerController::Control(PlayerController::KeyState::pressed, PlayerController::ControllerKey::dPadUp));
	playerController->AddCommand(std::move(moveDownCommmand), PlayerController::Control(PlayerController::KeyState::pressed, PlayerController::ControllerKey::dPadDown));
	//add the playerController to the inputManager
	dae::InputManager::GetInstance().AddController(std::move(playerController));
	scene.Add(std::move(go));
	
	go = std::make_shared<dae::GameObject>();
	go->SetLocalPosition(330.f, 300.f);
	renderComponent = std::make_unique<RenderComponent>(go.get(), "PeterPepperFrontFacing.png");
	go->AddComponent(std::move(renderComponent));
	moveSpeed = moveSpeed * 2.f;
	//create moveLeftCommand
	moveLeftCommmand = std::make_unique<commands::MoveLeftCommand>(go.get(), moveSpeed);
	//create moveRightCommand
	moveRightCommmand = std::make_unique<commands::MoveRightCommand>(go.get(), moveSpeed);
	//create moveUpCommand
	moveUpCommmand = std::make_unique<commands::MoveUpCommand>(go.get(), moveSpeed);
	//create moveUpCommand
	moveDownCommmand = std::make_unique<commands::MoveDownCommand>(go.get(), moveSpeed);
	//creat playerController
	playerController = std::make_unique<PlayerController>();
	//add the commands to the player controller
	playerController->AddCommand(std::move(moveLeftCommmand), PlayerController::KeyboardKey(PlayerController::KeyState::pressed, 'A'));
	playerController->AddCommand(std::move(moveRightCommmand), PlayerController::KeyboardKey(PlayerController::KeyState::pressed, 'D'));
	playerController->AddCommand(std::move(moveUpCommmand), PlayerController::KeyboardKey(PlayerController::KeyState::pressed, 'W'));
	playerController->AddCommand(std::move(moveDownCommmand), PlayerController::KeyboardKey(PlayerController::KeyState::pressed, 'S'));
	//add the playerController to the inputManager
	dae::InputManager::GetInstance().AddController(std::move(playerController));
	scene.Add(std::move(go));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}