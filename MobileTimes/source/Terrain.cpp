#include "Terrain.h"

using ut::Terrain;

Terrain::Terrain()
{}
Terrain::~Terrain()
{}

ut::ExitCode Terrain::set_tile(const size_t& dcX,
	const size_t& dcY, const Terrain::Tile& dcTile)
{
	auto result = ut::ExitCode::okay;
	try
	{
		mTiles.at(dcY).at(dcX) = dcTile;
		mTiles[dcY][dcX].position = sf::Vector2<size_t>(dcX, dcY);
	} catch (const std::out_of_range&) {
		result = ut::ExitCode::badInput;
	}
	return result;
}

ut::ExitCode Terrain::init_self(const size_t& dcSizeX,
	const size_t& dcSizeY)
{
	auto result = ut::ExitCode::okay;
	mTiles.clear();
	for (size_t y = 0; y < dcSizeY; ++y)
	{
		mTiles.push_back(std::vector<Terrain::Tile>(dcSizeX));
	}
	for (size_t y = 0; y < dcSizeY; ++y)
	{
		for (size_t x = 0; x < dcSizeX; ++x)
		{
			mTiles[y][x].position = sf::Vector2<size_t>(x, y);
		}
	}
	mSize.x = dcSizeX;
	mSize.y = dcSizeY;
	return result;
}