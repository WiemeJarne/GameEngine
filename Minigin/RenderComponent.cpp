#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"

RenderComponent::RenderComponent(std::weak_ptr<dae::GameObject> owner)
	: Component(owner)
{}

RenderComponent::RenderComponent(std::weak_ptr<dae::GameObject> owner, const std::string& textureFilename)
	: Component(owner)
{
	SetTextureComponent(textureFilename);
}

RenderComponent::RenderComponent(std::weak_ptr<dae::GameObject> owner, std::shared_ptr<dae::TextureComponent> textureComponent)
	: Component(owner)
{
	SetTextureComponent(textureComponent);
}

void RenderComponent::Render() const
{
	const auto& pos = m_Owner.lock()->GetWorldPos();

	if (m_TextureComponent)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_TextureComponent, pos.x, pos.y);
	}
}

void RenderComponent::SetTextureComponent(const std::string& filename)
{
	m_TextureComponent = std::make_shared<dae::TextureComponent>(m_Owner, filename);
}

void RenderComponent::SetTextureComponent(std::shared_ptr<dae::TextureComponent> textureComponent)
{
	m_TextureComponent = textureComponent;
}