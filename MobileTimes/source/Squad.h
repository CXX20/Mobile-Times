#ifndef UTHEADER_SQUAD
#define UTHEADER_SQUAD
#include <array>
#include <SFML\System\Vector2.hpp>
#include "Unit.h"

namespace ut {
class Squad
{
public:
	Squad();
	Squad(const int& dcId, const bool& dcIsActive,
		const SpriteType&, const sf::Vector2<size_t>&,
		const int& dcMoney);

	virtual ~Squad();
	
	static const size_t sncUnitsPerSquad = 8;

	const int& get_id() const
	{
		return mId;
	}
	const bool& get_isActive() const
	{
		return mIsActive;
	}
	const auto& get_spriteType() const
	{
		return mSpriteType;
	}
	const auto& get_position() const
	{
		return mPosition;
	}

	void set_position(const sf::Vector2<size_t>& dcPosition)
	{
		mPosition = dcPosition;
	}

private:
	int mId;
	bool mIsActive;
	SpriteType mSpriteType;
	sf::Vector2<size_t> mPosition;
	std::array<Unit, sncUnitsPerSquad> mUnits;
	int mMoney;
};
} // namespace ut;

#endif // ! UTHEADER_SQUAD;