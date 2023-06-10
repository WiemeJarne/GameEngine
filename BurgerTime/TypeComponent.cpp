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

	using KeyState = dae::KeyState;
	using KeyboardKey = dae::InputManager::KeyboardKey;
	
	dae::InputManager::GetInstance().AddCommand(std::move(commandA), KeyState::down, KeyboardKey::A);
	dae::InputManager::GetInstance().AddCommand(std::move(commandB), KeyState::down, KeyboardKey::B);
	dae::InputManager::GetInstance().AddCommand(std::move(commandC), KeyState::down, KeyboardKey::C);
	dae::InputManager::GetInstance().AddCommand(std::move(commandD), KeyState::down, KeyboardKey::D);
	dae::InputManager::GetInstance().AddCommand(std::move(commandE), KeyState::down, KeyboardKey::E);
	dae::InputManager::GetInstance().AddCommand(std::move(commandF), KeyState::down, KeyboardKey::F);
	dae::InputManager::GetInstance().AddCommand(std::move(commandG), KeyState::down, KeyboardKey::G);
	dae::InputManager::GetInstance().AddCommand(std::move(commandH), KeyState::down, KeyboardKey::H);
	dae::InputManager::GetInstance().AddCommand(std::move(commandI), KeyState::down, KeyboardKey::I);
	dae::InputManager::GetInstance().AddCommand(std::move(commandJ), KeyState::down, KeyboardKey::J);
	dae::InputManager::GetInstance().AddCommand(std::move(commandK), KeyState::down, KeyboardKey::K);
	dae::InputManager::GetInstance().AddCommand(std::move(commandL), KeyState::down, KeyboardKey::L);
	dae::InputManager::GetInstance().AddCommand(std::move(commandM), KeyState::down, KeyboardKey::M);
	dae::InputManager::GetInstance().AddCommand(std::move(commandN), KeyState::down, KeyboardKey::N);
	dae::InputManager::GetInstance().AddCommand(std::move(commandO), KeyState::down, KeyboardKey::O);
	dae::InputManager::GetInstance().AddCommand(std::move(commandP), KeyState::down, KeyboardKey::P);
	dae::InputManager::GetInstance().AddCommand(std::move(commandQ), KeyState::down, KeyboardKey::Q);
	dae::InputManager::GetInstance().AddCommand(std::move(commandR), KeyState::down, KeyboardKey::R);
	dae::InputManager::GetInstance().AddCommand(std::move(commandS), KeyState::down, KeyboardKey::S);
	dae::InputManager::GetInstance().AddCommand(std::move(commandT), KeyState::down, KeyboardKey::T);
	dae::InputManager::GetInstance().AddCommand(std::move(commandU), KeyState::down, KeyboardKey::U);
	dae::InputManager::GetInstance().AddCommand(std::move(commandV), KeyState::down, KeyboardKey::V);
	dae::InputManager::GetInstance().AddCommand(std::move(commandW), KeyState::down, KeyboardKey::W);
	dae::InputManager::GetInstance().AddCommand(std::move(commandX), KeyState::down, KeyboardKey::X);
	dae::InputManager::GetInstance().AddCommand(std::move(commandY), KeyState::down, KeyboardKey::Y);
	dae::InputManager::GetInstance().AddCommand(std::move(commandZ), KeyState::down, KeyboardKey::Z);
	dae::InputManager::GetInstance().AddCommand(std::move(commandDash), KeyState::down, KeyboardKey::Minus);
	dae::InputManager::GetInstance().AddCommand(std::move(commandBackSpace), KeyState::down, KeyboardKey::BackSpace);
	dae::InputManager::GetInstance().AddCommand(std::move(commandSpace), KeyState::down, KeyboardKey::Space);

	pOwner->AddComponent(std::move(textComponent));
}