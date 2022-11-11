#pragma once
#include "Functions.h"

//Global variables
namespace Globals
{
	
    const std::string PreviewTilesetPath = Functions::getProjectDirectory() + "/images/Tileset.png";
	const std::string FontPath = "Fonts/Stan.ttf";
	const sf::Vector2i PreviewTilesetTiling = { 8, 2 };
	const sf::Vector2i StartTilemapSize = { 10, 10 };
	const int MaxTileMapSize = 30;
	const int MinTileMapSize = 3;
}