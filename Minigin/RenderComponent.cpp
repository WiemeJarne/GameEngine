#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

RenderComponent::~RenderComponent() = default;

void RenderComponent::Update() {}

void RenderComponent::Render(const dae::GameObject& go) const
{
	const auto& pos = go.GetTransform().GetPosition();

	std::shared_ptr<dae::Texture2D> texture{ go.GetComponent<dae::Texture2D>()};
	if (texture)
	{
		dae::Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}
}