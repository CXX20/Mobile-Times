#include "Squad.h"

using ut::Squad;

Squad::Squad()
{
	mId = ut::glb::NegativeId::scError;
	mIsActive = false;
	mSpriteType = ut::SpriteType::error;
	mPosition = sf::Vector2<size_t>(0, 0);
	mMoney = 0;
}
Squad::Squad(const int& dcId, const bool& dcIsActive,
	const ut::SpriteType& dcSpriteType,
	const sf::Vector2<size_t>& dcPosition, const int& dcMoney)
{
	mId = dcId;
	mIsActive = dcIsActive;
	mSpriteType = dcSpriteType;
	mPosition = dcPosition;
	mMoney = dcMoney;
}
Squad::~Squad()
{}