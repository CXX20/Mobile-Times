#include "Sprite.h"

using ut::Sprite;

Sprite::Sprite()
{}
Sprite::~Sprite()
{}

void Sprite::set_render(const ut::Render& dcRender)
{
	const sf::Vector2f cLeftTop(dcRender.position.left,
		dcRender.position.top);
	mSprite.setPosition(cLeftTop);
	const sf::FloatRect cLocalBounds = mSprite.getLocalBounds();
	const sf::Vector2f cSize(cLocalBounds.width, cLocalBounds.height);
	const sf::Vector2f dcSize(dcRender.position.width,
		dcRender.position.height);
	sf::Vector2f scale(dcSize.x/cSize.x, dcSize.y/cSize.y);
	mSprite.setScale(scale);
	// TODO rotation;
}

ut::ExitCode Sprite::init_self(const std::string& dcFileName)
{
	ut::ExitCode result;
	bool isLoaded = mImage.loadFromFile(dcFileName);
	if (isLoaded)
	{
		mFileName = dcFileName;
		mTexture.loadFromImage(mImage);
		mSprite.setTexture(mTexture);
		result = ut::ExitCode::okay;
	} else {
		result = ut::ExitCode::noFile;
	}
	return result;
}