#include <SDL.h>
#include "TextureComponent.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename)
	:m_texture{ dae::ResourceManager::GetInstance().LoadTexture(filename) }
{ }

dae::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_texture);
}

void dae::TextureComponent::Update() {}

glm::ivec2 dae::TextureComponent::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* dae::TextureComponent::GetSDLTexture() const
{
	return m_texture;
}

dae::TextureComponent::TextureComponent(SDL_Texture* texture)
{
	m_texture = texture;
}