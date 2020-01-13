#ifndef UTHEADER_UNIT
#define UTHEADER_UNIT
#include "globals.h"
#include "SpriteType.h"

namespace ut {
class Unit
{
public:
	Unit();
	virtual ~Unit();

	const auto& get_spriteType() const
	{
		return mSpriteType;
	}

private:
	bool mIsAlive;
	SpriteType mSpriteType;
};
} // namespace ut;

#endif // ! UTHEADER_UNIT;