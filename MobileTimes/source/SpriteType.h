#ifndef UTHEADER_SPRITE_TYPE
#define UTHEADER_SPRITE_TYPE

namespace ut {
enum class SpriteType : int
{
	// error (always the first):
	error,
	// none (always the second):
	none,
	// ?gui:
	buttonGreen,
	// for Squad:
	squadKnight
	// for Unit:
};
} // namespace ut;

#endif // ! UTHEADER_SPRITE_TYPE;