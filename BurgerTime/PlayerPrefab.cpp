#include "PlayerPrefab.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "MoveComponent.h"
#include "MoveCommand.h"
#include "playerController.h"
#include "InputManager.h"
#include "CollisionBoxComponent.h"
#include "ThumbstickMoveCommand.h"
#include "Scene.h"
#include "PepperComponent.h"
#include "UsePepperCommand.h"

PlayerPrefab::PlayerPrefab(dae::Scene* pScene, const std::string& textureFilePath, const glm::vec2& pos, const glm::vec2& healthVisualizationPos, const std::string& healthVisualizationTextureFilepath, int amountOfLives, bool useKeyboard, float moveSpeed)
{
	m_go = std::make_unique<dae::GameObject>(pScene);
	m_go->SetLocalPosition(pos.x, pos.y);
	auto renderComponent{ std::make_unique<dae::RenderComponent>(m_go.get(), textureFilePath) };
	auto healthComponent{ std::make_unique<HealthComponent>(m_go.get(), amountOfLives, healthVisualizationPos, healthVisualizationTextureFilepath) };
	auto moveComponent{ std::make_unique<MoveComponent>(m_go.get(), moveSpeed) };
	const auto textureSize{ renderComponent->GetTextureComponent()->GetSize()};
	auto collisionBoxComponent{ std::make_unique<dae::CollisionBoxComponent>(m_go.get(), static_cast<float>(textureSize.x), static_cast<float>(textureSize.y)) };
	auto pepperComponent{ std::make_unique<PepperComponent>(m_go.get(), 3, glm::vec2(healthVisualizationPos.x, healthVisualizationPos.y + 20.f)) };

	m_go->AddComponent(std::move(renderComponent));
	m_go->AddComponent(std::move(healthComponent));
	m_go->AddComponent(std::move(moveComponent));
	m_go->AddComponent(std::move(collisionBoxComponent));
	
	//create controller commands
	//create thumbstickMoveCommand
	auto thumbstickMoveCommand = std::make_unique<commands::ThumbstickMoveCommand>(m_go.get());
	auto controllerUsePepperCommand = std::make_unique<commands::UsePepperCommand>(pepperComponent.get());
	
	//controler input
	auto playerController{ std::make_unique<dae::PlayerController>(-1) };
	playerController->InvertThumbstickLeftYAxis();
	playerController->AddCommand(std::move(thumbstickMoveCommand), dae::PlayerController::ControllerAxis::tumbStickLeft);
	playerController->AddCommand(std::move(controllerUsePepperCommand), dae::PlayerController::Control(dae::KeyState::down, dae::PlayerController::ControllerKey::A));
	dae::InputManager::GetInstance().AddController(std::move(playerController));

	//create keyboard commands
	//create moveLeftCommand
	auto moveLeftCommmand = std::make_unique<commands::MoveCommand>(m_go.get(), glm::vec2(-1.f, 0.f));
	//create moveRightCommand
	auto moveRightCommmand = std::make_unique<commands::MoveCommand>(m_go.get(), glm::vec2(1.f, 0.f));
	//create moveUpCommand
	auto moveUpCommmand = std::make_unique<commands::MoveCommand>(m_go.get(), glm::vec2(0.f, -1.f));
	//create moveUpCommand
	auto moveDownCommmand = std::make_unique<commands::MoveCommand>(m_go.get(), glm::vec2(0.f, 1.f));
	//create usePepperCommand
	auto usePepperCommand = std::make_unique<commands::UsePepperCommand>(pepperComponent.get());

	m_go->AddComponent(std::move(pepperComponent));
	
	//keyboard input
	if (useKeyboard)
	{
		dae::InputManager::GetInstance().AddCommand(std::move(moveLeftCommmand), dae::KeyState::pressed, dae::InputManager::KeyboardKey::A);
		dae::InputManager::GetInstance().AddCommand(std::move(moveRightCommmand), dae::KeyState::pressed, dae::InputManager::KeyboardKey::D);
		dae::InputManager::GetInstance().AddCommand(std::move(moveUpCommmand), dae::KeyState::pressed, dae::InputManager::KeyboardKey::W);
		dae::InputManager::GetInstance().AddCommand(std::move(moveDownCommmand), dae::KeyState::pressed, dae::InputManager::KeyboardKey::S);
		dae::InputManager::GetInstance().AddCommand(std::move(usePepperCommand), dae::KeyState::down, dae::InputManager::KeyboardKey::E);
	}
}