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
	class Texture2D final : public Component
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		Texture2D(const std::string& filename);
		Texture2D(SDL_Texture* texture);
		~Texture2D();

		virtual void Update() override;
		glm::ivec2 GetSize() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

	private:
		SDL_Texture* m_texture;
	};
}
