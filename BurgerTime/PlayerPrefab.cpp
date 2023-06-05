#include "PlayerPrefab.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "MoveComponent.h"
#include "Command.h"
#include "MoveCommand.h"
#include "playerController.h"
#include "InputManager.h"
#include "CollisionBoxComponent.h"
#include "ThumbstickMoveCommand.h"
#include "Scene.h"

PlayerPrefab::PlayerPrefab(dae::Scene* pScene, const std::string& textureFilePath, int amountOfLives, const glm::vec2& pos, bool useKeyboard, float moveSpeed)
{
	m_go = std::make_unique<dae::GameObject>(pScene);
	m_go->SetLocalPosition(pos.x, pos.y);
	auto renderComponent{ std::make_unique<RenderComponent>(m_go.get(), textureFilePath) };
	auto healthComponent{ std::make_unique<HealthComponent>(m_go.get(), amountOfLives) };
	auto moveComponent{ std::make_unique<MoveComponent>(m_go.get(), moveSpeed) };
	auto textureSize{ renderComponent->GetTextureComponent()->GetSize()};
	auto collisionBoxComponent{ std::make_unique<dae::CollisionBoxComponent>(m_go.get(), static_cast<float>(textureSize.x), static_cast<float>(textureSize.y)) };

	m_go->AddComponent(std::move(renderComponent));
	m_go->AddComponent(std::move(healthComponent));
	m_go->AddComponent(std::move(moveComponent));
	m_go->AddComponent(std::move(collisionBoxComponent));
	
	//create controller commands
	//create thumbstickMoveCommand
	auto thumbstickMoveCommand = std::make_unique<commands::ThumbstickMoveCommand>(m_go.get());
	
	//controler input
	auto playerController{ std::make_unique<PlayerController>(-1) };
	playerController->InvertThumbstickLeftYAxis();
	playerController->AddCommand(std::move(thumbstickMoveCommand), PlayerController::ControllerAxis::tumbStickLeft);
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
	
	//keyboard input
	if (useKeyboard)
	{
		dae::InputManager::GetInstance().AddCommand(std::move(moveLeftCommmand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'A'));
		dae::InputManager::GetInstance().AddCommand(std::move(moveRightCommmand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'D'));
		dae::InputManager::GetInstance().AddCommand(std::move(moveUpCommmand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'W'));
		dae::InputManager::GetInstance().AddCommand(std::move(moveDownCommmand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'S'));
	}
}