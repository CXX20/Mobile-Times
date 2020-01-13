#ifndef UTHEADER_SPRITE
#define UTHEADER_SPRITE
#include <string>
#include <SFML\Graphics.hpp>
#include "ExitCode.h"
#include "Render.h"
#include "SpriteType.h"

namespace ut {
class Sprite : public sf::Drawable
{
public:
	Sprite();
	virtual ~Sprite();

	virtual void draw(sf::RenderTarget& target,
		const sf::RenderStates cState) const
	{
		target.draw(mSprite, cState);
	}

	const auto& get_fileName()
	{
		return mFileName;
	}

	void set_render(const Render&);

	ExitCode init_self(const std::string&);

private:
	std::string mFileName;
	sf::Image mImage;
	sf::Texture mTexture;
	sf::Sprite mSprite;
};
} // namespace ut;

#endif // ! UTHEADER_SPRITE;