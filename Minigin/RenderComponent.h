#pragma once
#include <memory>
#include <string>
#include "Component.h"

namespace dae
{
	class GameObject;
}

class RenderComponent final : public Component
{
public:
	RenderComponent() = default;
	virtual ~RenderComponent();
	RenderComponent(const RenderComponent& other) = delete;
	RenderComponent(RenderComponent&& other) = delete;
	RenderComponent& operator=(const RenderComponent& other) = delete;
	RenderComponent& operator=(RenderComponent&& other) = delete;

	virtual void Update() override;
	virtual void Render(const dae::GameObject& go) const override;
};

