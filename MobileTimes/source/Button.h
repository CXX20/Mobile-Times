#ifndef UTHEADER_BUTTON
#define UTHEADER_BUTTON
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\Text.hpp>
#include "globals.h"
#include "SpriteType.h"

namespace ut {
class Button
{
public:
	enum class State
	{
		disabled,
		// but visible;
		unclickable,
		active,
		hovered,
		// but not released yet;
		holded
	};
	enum class Type
	{
		error,
		play
	};

	Button();
	Button(const Type&);
	virtual ~Button();

	const auto& get_type() const
	{
		return mType;
	}
	const auto& get_state() const
	{
		return mState;
	}
	const auto& get_spriteType() const
	{
		return mSpriteType;
	}
	const auto& get_position() const
	{
		return mPosition;
	}

	void set_state(const State& dcState)
	{
		mState = dcState;
	}

	bool is_hovered(const sf::Vector2i&) const;

private:
	Type mType;
	State mState;
	SpriteType mSpriteType;
	// TODO ? in Tile
	sf::FloatRect mPosition;
	sf::Text mText;
};
} // namespace ut;

#endif // ! UTHEADER_BUTTON;