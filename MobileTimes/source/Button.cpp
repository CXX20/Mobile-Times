#include "Button.h"

using ut::Button;

Button::Button()
{
	mType = Type::error;
	mState = State::disabled;
	mSpriteType = SpriteType::error;
}
Button::Button(const Type& dcType)
{
	mType = dcType;
	mState = State::active;
	// DEBUG spriteType:
	mSpriteType = SpriteType::buttonGreen;
	sf::FloatRect dPosition;
	switch (dcType)
	{
	case Type::play:
		// DEBUG FloatRect for Button::Type::play:
		dPosition = sf::FloatRect(
			static_cast<float>(ut::glb::ncPixelsPerTile * 3u),
			static_cast<float>(ut::glb::ncPixelsPerTile * 2u),
			static_cast<float>(ut::glb::ncPixelsPerTile * 6u),
			static_cast<float>(ut::glb::ncPixelsPerTile * 2u));
		break;
	default:
		assert(false);
		break;
	}
	mPosition = dPosition;
}
Button::~Button()
{}

bool Button::is_hovered(const sf::Vector2i& cClickPosition) const
{
	if (IS_RIGHT_UNSTRICT_INEQUALITY(mPosition.left, cClickPosition.x,
			mPosition.left+mPosition.width) &&
		IS_RIGHT_UNSTRICT_INEQUALITY(mPosition.top, cClickPosition.y,
			mPosition.top+mPosition.height))
	{
		return true;
	}
	return false;
}