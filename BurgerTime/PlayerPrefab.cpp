#include "PlayerPrefab.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "PointsComponent.h"
#include "MoveComponent.h"
#include "Command.h"
#include "MoveCommand.h"
#include "DamageCommand.h"
#include "PointsCommand.h"
#include "playerController.h"
#include "InputManager.h"
#include "CollisionBoxComponent.h"

PlayerPrefab::PlayerPrefab(const std::string& textureFilePath, int amountOfLives, const glm::vec2& pos, bool useController, float moveSpeed)
{
	m_go = std::make_unique<dae::GameObject>();
	m_go->SetLocalPosition(pos.x, pos.y);
	auto renderComponent{ std::make_unique<RenderComponent>(m_go.get(), textureFilePath) };
	auto healthComponent{ std::make_unique<HealthComponent>(m_go.get(), amountOfLives) };
	auto pointsComponent{ std::make_unique<PointsComponent>(m_go.get()) };
	auto moveComponent{ std::make_unique<MoveComponent>(m_go.get(), moveSpeed) };
	auto textureSize{ renderComponent->GetTextureComponent()->GetSize()};
	auto collisionBoxComponent{ std::make_unique<dae::CollisionBoxComponent>(m_go.get(), static_cast<float>(textureSize.x), static_cast<float>(textureSize.y)) };

	m_go->AddComponent(std::move(renderComponent));
	m_go->AddComponent(std::move(healthComponent));
	m_go->AddComponent(std::move(pointsComponent));
	m_go->AddComponent(std::move(moveComponent));
	m_go->AddComponent(std::move(collisionBoxComponent));
	
	//create moveLeftCommand
	auto moveLeftCommmand = std::make_unique<commands::MoveCommand>(m_go.get(), glm::vec2(-1.f, 0.f));
	//create moveRightCommand
	auto moveRightCommmand = std::make_unique<commands::MoveCommand>(m_go.get(), glm::vec2(1.f, 0.f));
	//create moveUpCommand
	auto moveUpCommmand = std::make_unique<commands::MoveCommand>(m_go.get(), glm::vec2(0.f, -1.f));
	//create moveUpCommand
	auto moveDownCommmand = std::make_unique<commands::MoveCommand>(m_go.get(), glm::vec2(0.f, 1.f));
	//create damageCommand
	auto damageCommand{ std::make_unique<commands::DamageCommand>(m_go.get(), 1) };
	//create pointsCommand
	auto pointsCommand{ std::make_unique<commands::PointsCommmand>(m_go.get(), 1) };

	if (useController)
	{
		//with -1 used as controller index the next avaialible index will be used
		auto playerController{ std::make_unique<PlayerController>(-1) };
		playerController->AddCommand(std::move(moveLeftCommmand), PlayerController::Control(dae::KeyState::pressed, PlayerController::ControllerKey::dPadLeft));
		playerController->AddCommand(std::move(moveRightCommmand), PlayerController::Control(dae::KeyState::pressed, PlayerController::ControllerKey::dPadRight));
		playerController->AddCommand(std::move(moveUpCommmand), PlayerController::Control(dae::KeyState::pressed, PlayerController::ControllerKey::dPadUp));
		playerController->AddCommand(std::move(moveDownCommmand), PlayerController::Control(dae::KeyState::pressed, PlayerController::ControllerKey::dPadDown));
		playerController->AddCommand(std::move(damageCommand), PlayerController::Control(dae::KeyState::down, PlayerController::ControllerKey::shoulderRight));
		playerController->AddCommand(std::move(pointsCommand), PlayerController::Control(dae::KeyState::down, PlayerController::ControllerKey::A));
		dae::InputManager::GetInstance().AddController(std::move(playerController));
	}
	else
	{
		dae::InputManager::GetInstance().AddCommand(std::move(moveLeftCommmand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'A'));
		dae::InputManager::GetInstance().AddCommand(std::move(moveRightCommmand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'D'));
		dae::InputManager::GetInstance().AddCommand(std::move(moveUpCommmand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'W'));
		dae::InputManager::GetInstance().AddCommand(std::move(moveDownCommmand), dae::InputManager::KeyboardKey(dae::KeyState::pressed, 'S'));
		dae::InputManager::GetInstance().AddCommand(std::move(damageCommand), dae::InputManager::KeyboardKey(dae::KeyState::down, ' '));
		dae::InputManager::GetInstance().AddCommand(std::move(pointsCommand), dae::InputManager::KeyboardKey(dae::KeyState::down, 'P'));
	}
}