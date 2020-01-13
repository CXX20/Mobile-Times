#ifndef UTHEADER_RENDER
#define UTHEADER_RENDER
#include "Button.h"
#include "Terrain.h"
#include "Squad.h"

namespace ut {
struct Render
{
	enum class Priority;

	Render();
	Render(const Button&);
	// bool for spriteType or spriteType2:
	Render(const Terrain::Tile&);
	Render(const Squad&);
	Render(const Unit&);
	virtual ~Render();

	Priority priority;
	SpriteType spriteType;
	sf::FloatRect position;
	float rotation;

	bool operator<(const Render& cOther) const;
};
} // namespace ut;

#endif // ! UTHEADER_RENDER;
