#include "Render.h"

using ut::Render;

enum class Render::Priority
{
	background,
	character,
	building,
	interface,
	text,
	// always max:
	error
};

Render::Render()
{
	priority = Priority::error;
	spriteType = ut::SpriteType::error;
	rotation = 0.0f;
}
Render::Render(const ut::Button& dcButton)
{
	spriteType = dcButton.get_spriteType();
	priority = Priority::interface;
	position = dcButton.get_position();
	rotation = 0.0f;
}
Render::Render(const ut::Terrain::Tile& dcTile)
{
	spriteType = dcTile.spriteType;
	priority = Priority::background;
	position = sf::FloatRect(
		static_cast<float>(ut::glb::ncPixelsPerTile * dcTile.position.x),
		static_cast<float>(ut::glb::ncPixelsPerTile * dcTile.position.y),
		static_cast<float>(ut::glb::ncPixelsPerTile),
		static_cast<float>(ut::glb::ncPixelsPerTile));
	rotation = 0.0f;
}
Render::Render(const ut::Squad& dcSquad)
{
	if (dcSquad.get_isActive())
	{
		spriteType = dcSquad.get_spriteType();
	} else {
		spriteType = ut::SpriteType::none;
	}
	priority = Priority::character;
	position = sf::FloatRect(
		static_cast<float>(ut::glb::ncPixelsPerTile*dcSquad.get_position().x),
		static_cast<float>(ut::glb::ncPixelsPerTile*dcSquad.get_position().y),
		static_cast<float>(ut::glb::ncPixelsPerTile)*1.5f,
		static_cast<float>(ut::glb::ncPixelsPerTile)*1.5f);
	position.top -= static_cast<float>(ut::glb::ncPixelsPerTile)*0.67f;
	rotation = 0.0f;
}
Render::Render(const ut::Unit& dcUnit)
{
	spriteType = dcUnit.get_spriteType();
	priority = Priority::character;
	// TODO position;
	rotation = 0.0f;
}
Render::~Render()
{}

bool Render::operator<(const Render& cOther) const
{
	IF_UNEQUAL_RETURN_IS_LESS(priority, cOther.priority);
	IF_UNEQUAL_RETURN_IS_LESS(spriteType, cOther.spriteType);
	IF_UNEQUAL_RETURN_IS_LESS(position.left, cOther.position.left);
	IF_UNEQUAL_RETURN_IS_LESS(position.top, cOther.position.top);
	IF_UNEQUAL_RETURN_IS_LESS(position.width, cOther.position.width);
	IF_UNEQUAL_RETURN_IS_LESS(position.height, cOther.position.height);
	return rotation < cOther.rotation;
}