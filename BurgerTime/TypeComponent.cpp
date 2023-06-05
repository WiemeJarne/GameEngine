#include "TypeComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TypeCommand.h"

TypeComponent::TypeComponent(dae::GameObject* pOwner, std::shared_ptr<dae::Font> font)
	: Component(pOwner)
{
	auto textComponent{ std::make_unique<dae::TextComponent>(pOwner, "_", font) };

	using namespace commands;

	auto commandA = std::make_unique<TypeCommand>('A', textComponent.get());
	auto commandB = std::make_unique<TypeCommand>('B', textComponent.get());
	auto commandC = std::make_unique<TypeCommand>('C', textComponent.get());
	auto commandD = std::make_unique<TypeCommand>('D', textComponent.get());
	auto commandE = std::make_unique<TypeCommand>('E', textComponent.get());
	auto commandF = std::make_unique<TypeCommand>('F', textComponent.get());
	auto commandG = std::make_unique<TypeCommand>('G', textComponent.get());
	auto commandH = std::make_unique<TypeCommand>('H', textComponent.get());
	auto commandI = std::make_unique<TypeCommand>('I', textComponent.get());
	auto commandJ = std::make_unique<TypeCommand>('J', textComponent.get());
	auto commandK = std::make_unique<TypeCommand>('K', textComponent.get());
	auto commandL = std::make_unique<TypeCommand>('L', textComponent.get());
	auto commandM = std::make_unique<TypeCommand>('M', textComponent.get());
	auto commandN = std::make_unique<TypeCommand>('N', textComponent.get());
	auto commandO = std::make_unique<TypeCommand>('O', textComponent.get());
	auto commandP = std::make_unique<TypeCommand>('P', textComponent.get());
	auto commandQ = std::make_unique<TypeCommand>('Q', textComponent.get());
	auto commandR = std::make_unique<TypeCommand>('R', textComponent.get());
	auto commandS = std::make_unique<TypeCommand>('S', textComponent.get());
	auto commandT = std::make_unique<TypeCommand>('T', textComponent.get());
	auto commandU = std::make_unique<TypeCommand>('U', textComponent.get());
	auto commandV = std::make_unique<TypeCommand>('V', textComponent.get());
	auto commandW = std::make_unique<TypeCommand>('W', textComponent.get());
	auto commandX = std::make_unique<TypeCommand>('X', textComponent.get());
	auto commandY = std::make_unique<TypeCommand>('Y', textComponent.get());
	auto commandZ = std::make_unique<TypeCommand>('Z', textComponent.get());
	auto commandDash = std::make_unique<TypeCommand>('-', textComponent.get());
	auto commandBackSpace = std::make_unique<TypeCommand>('\b', textComponent.get());
	auto commandSpace = std::make_unique<TypeCommand>(' ', textComponent.get());

	dae::InputManager::GetInstance().AddCommand(std::move(commandA), dae::InputManager::KeyboardKey(dae::KeyState::down, 'A'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandB), dae::InputManager::KeyboardKey(dae::KeyState::down, 'B'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandC), dae::InputManager::KeyboardKey(dae::KeyState::down, 'C'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandD), dae::InputManager::KeyboardKey(dae::KeyState::down, 'D'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandE), dae::InputManager::KeyboardKey(dae::KeyState::down, 'E'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandF), dae::InputManager::KeyboardKey(dae::KeyState::down, 'F'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandG), dae::InputManager::KeyboardKey(dae::KeyState::down, 'G'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandH), dae::InputManager::KeyboardKey(dae::KeyState::down, 'H'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandI), dae::InputManager::KeyboardKey(dae::KeyState::down, 'I'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandJ), dae::InputManager::KeyboardKey(dae::KeyState::down, 'J'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandK), dae::InputManager::KeyboardKey(dae::KeyState::down, 'K'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandL), dae::InputManager::KeyboardKey(dae::KeyState::down, 'L'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandM), dae::InputManager::KeyboardKey(dae::KeyState::down, 'M'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandN), dae::InputManager::KeyboardKey(dae::KeyState::down, 'N'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandO), dae::InputManager::KeyboardKey(dae::KeyState::down, 'O'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandP), dae::InputManager::KeyboardKey(dae::KeyState::down, 'P'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandQ), dae::InputManager::KeyboardKey(dae::KeyState::down, 'Q'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandR), dae::InputManager::KeyboardKey(dae::KeyState::down, 'R'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandS), dae::InputManager::KeyboardKey(dae::KeyState::down, 'S'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandT), dae::InputManager::KeyboardKey(dae::KeyState::down, 'T'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandU), dae::InputManager::KeyboardKey(dae::KeyState::down, 'U'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandV), dae::InputManager::KeyboardKey(dae::KeyState::down, 'V'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandW), dae::InputManager::KeyboardKey(dae::KeyState::down, 'W'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandX), dae::InputManager::KeyboardKey(dae::KeyState::down, 'X'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandY), dae::InputManager::KeyboardKey(dae::KeyState::down, 'Y'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandZ), dae::InputManager::KeyboardKey(dae::KeyState::down, 'Z'));
	dae::InputManager::GetInstance().AddCommand(std::move(commandDash), dae::InputManager::KeyboardKey(dae::KeyState::down, static_cast<int>(dae::SpecialKeyboardKey::Minus)), true);
	dae::InputManager::GetInstance().AddCommand(std::move(commandBackSpace), dae::InputManager::KeyboardKey(dae::KeyState::down, static_cast<int>(dae::SpecialKeyboardKey::BackSpace)), true);
	dae::InputManager::GetInstance().AddCommand(std::move(commandSpace), dae::InputManager::KeyboardKey(dae::KeyState::down, static_cast<int>(dae::SpecialKeyboardKey::Space)), true);

	pOwner->AddComponent(std::move(textComponent));
}