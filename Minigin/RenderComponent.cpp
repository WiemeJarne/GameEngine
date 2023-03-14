#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <iostream>

RenderComponent::RenderComponent(dae::GameObject* owner)
	: Component(owner)
{}

RenderComponent::RenderComponent(dae::GameObject* owner, const std::string& textureFilename)
	: Component(owner)
{
	SetTextureComponent(textureFilename);
}

RenderComponent::RenderComponent(dae::GameObject* owner, std::shared_ptr<dae::TextureComponent> textureComponent)
	: Component(owner)
{
	SetTextureComponent(textureComponent);
}

void RenderComponent::Render() const
{
	auto pos = m_Owner->GetWorldPos();

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