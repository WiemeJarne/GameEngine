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
#include <iostream>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<dae::GameObject>();
	//auto renderComponent = std::make_shared<RenderComponent>(go.get(), "background.tga");
	//go->AddComponent(renderComponent);
	//scene.Add(go);
	//
	//go = std::make_shared<dae::GameObject>();
	//renderComponent = std::make_shared<RenderComponent>(go.get(), "logo.tga");
	//go->AddComponent(renderComponent);
	//go->SetWorldPosition(216, 180);
	//scene.Add(go);
	//
	//go = std::make_shared<dae::GameObject>();
	//go->SetWorldPosition(80, 20);
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextComponent>(go.get(), "Programming 4 Assignment", font, nullptr);
	//renderComponent = std::make_shared<RenderComponent>(go.get(), to->GetTexture());
	//go->AddComponent(to);
	//go->AddComponent(renderComponent);
	//scene.Add(go);
	//
	//go = std::make_shared<dae::GameObject>();
	//renderComponent = std::make_shared<RenderComponent>(go.get());
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	//to = std::make_shared<dae::TextComponent>(go.get(), "0", font, renderComponent);
	//auto fpsComponent = std::make_shared<FPSComponent>(go.get(), to);
	//go->AddComponent(to);
	//go->AddComponent(renderComponent);
	//go->AddComponent(fpsComponent);
	//scene.Add(go);

	auto go = std::make_unique<dae::GameObject>();
	go->SetLocalPosition(320.f, 300.f); 
	auto renderComponent = std::make_unique<RenderComponent>(go.get(), "MrHotDog.png");
	go->AddComponent(std::move(renderComponent));
	auto moveInCircleComponent = std::make_unique<MoveInCircleComponent>(go.get(), 30.f, 10.f);
	go->AddComponent(std::move(moveInCircleComponent));
	
	auto go2 = std::make_unique<dae::GameObject>();
	go2->SetLocalPosition(320.f, 300.f);
	renderComponent = std::make_unique<RenderComponent>(go2.get(), "PeterPepperFrontFacing.png");
	go2->AddComponent(std::move(renderComponent));
	moveInCircleComponent = std::make_unique<MoveInCircleComponent>(go2.get(), 30.f, 5.f, false);
	go2->AddComponent(std::move(moveInCircleComponent));
	
	go->SetParent(go2.get(), true);

	scene.Add(std::move(go2));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}