#pragma once
#include <glm/vec2.hpp>
#include "Component.h"
#include <string>

struct SDL_Texture;
namespace dae
{
	/**
 * Simple RAII wrapper for an SDL_Texture
 */
	class TextureComponent final : public Component
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		TextureComponent() = default;
		TextureComponent(const std::string& filename);
		TextureComponent(SDL_Texture* texture);
		~TextureComponent();

		virtual void Update() override;
		glm::ivec2 GetSize() const;

		TextureComponent(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator= (const TextureComponent&) = delete;
		TextureComponent& operator= (const TextureComponent&&) = delete;

	private:
		SDL_Texture* m_texture;
	};
}