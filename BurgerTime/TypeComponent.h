#pragma once
#include "Component.h"
#include "Font.h"
#include  <memory>

class TypeComponent final : public dae::Component
{
public:
	TypeComponent(dae::GameObject* pOwner, std::shared_ptr<dae::Font> font);
	
	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
};