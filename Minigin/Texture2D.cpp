#include <SDL.h>
#include "Texture2D.h"
#include "ResourceManager.h"

dae::Texture2D::Texture2D(const std::string& filename)
	:m_texture{ dae::ResourceManager::GetInstance().LoadTexture(filename) }
{ }

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

void dae::Texture2D::Update() {}

glm::ivec2 dae::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_texture = texture;
}