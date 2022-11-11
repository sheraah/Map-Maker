#include "TilemapReader.h"
#include<fstream>
#include<sstream>

//constructor
TilemapReader::TilemapReader(const std::string& MapFilePath, sf::RenderWindow* window)
{
	init(MapFilePath, window);
}

TilemapReader::TilemapReader()
{

}

//init all variables from the map file
void TilemapReader::init(const std::string& MapFilePath, sf::RenderWindow* window)
{
	m_WindowRef = window;

	std::string Line;
	std::ifstream in(MapFilePath);
	std::stringstream ss;
	sf::Vector2i vec2;
	sf::Vector2i ImageTiling;

	if (!in.is_open())
	{
		throw "cant open mapFile!";
		return;
	}

	//1 line the texture path
	std::getline(in, Line);
	m_TilesetTexture.loadFromFile(Line);

	//2 Line the image tiling
	std::getline(in, Line);
	ss << Line;
	ss >> ImageTiling.x;
	ss >> ImageTiling.y;
	ss = std::stringstream();

	//3 Line for resizing the Tiles vector
	std::getline(in, Line);
	ss << Line;
	ss >> vec2.x;
	ss >> vec2.y;
	resizeTiles(vec2, m_WindowRef->getSize());

	//all other lines are the tiles
	// 1: the size of the layers vector
	// 2: the array index of the tile
	// 3: all draw indexes 
	// 4: the last number is the 0 or 1 (bool) collision 
	size_t totalTilesToDraw = 0;
	while (std::getline(in, Line))
	{
		ss = std::stringstream();

		size_t size = 0;
		bool collision = false;

		ss << Line;
		ss >> size;
		ss >> vec2.x;
		ss >> vec2.y;
		totalTilesToDraw += size;
		m_Tiles[vec2.x][vec2.y].indexes.resize(size);

		for (size_t i = 0; i < size; i++)
		{
			short index = 0;
			ss >> index;
			m_Tiles[vec2.x][vec2.y].indexes[i] = index;

			if (index == -1) totalTilesToDraw--;
		}

		ss >> collision;

		m_Tiles[vec2.x][vec2.y].collision = collision;
	}

	initVertexArray(totalTilesToDraw, ImageTiling, CalcTileSizeInImage(ImageTiling));
}

//init the vertex array the quads to draw
void TilemapReader::initVertexArray(const size_t& totalTiles, const sf::Vector2i& ImageTiling, const sf::Vector2i& TileSizeInImage)
{

	m_TilesToDraw.setPrimitiveType(sf::Quads);	
	m_TilesToDraw.resize(totalTiles * 4);

	size_t index = 0;

	for (size_t i = 0; i < m_Tiles.size(); i++)
		for (size_t j = 0; j < m_Tiles[i].size(); j++)
			for (size_t k = 0; k < m_Tiles[i][j].indexes.size(); k++)
			{
				short& drawIndex = m_Tiles[i][j].indexes[k];

				if (drawIndex == -1) continue;

				sf::Vector2f Pos = { 
					static_cast<float>(i * m_TileSize.x),
					static_cast<float>(j * m_TileSize.y)
				};

				sf::IntRect TexPos = calcRectOfIndexNumber(drawIndex, ImageTiling, TileSizeInImage);

				sf::Vector2f TopLeft =     { (float)TexPos.left, (float)TexPos.top };
				sf::Vector2f TopRight =    { (float)TexPos.left + TexPos.width, TopLeft.y };
				sf::Vector2f BottomLeft =  { (float)TopLeft.x, (float)TexPos.top + TexPos.height };
				sf::Vector2f BottonRight = { (float)TopRight.x, BottomLeft.y };

				m_TilesToDraw[index].position = Pos;
				m_TilesToDraw[index].texCoords = TopLeft;
				index++;
				m_TilesToDraw[index].position = { Pos.x + m_TileSize.x, Pos.y };
				m_TilesToDraw[index].texCoords = TopRight;
				index++;
				m_TilesToDraw[index].position = { Pos.x + m_TileSize.x, Pos.y + m_TileSize.y };
				m_TilesToDraw[index].texCoords = BottonRight;
				index++;
				m_TilesToDraw[index].position = { Pos.x, Pos.y + m_TileSize.y };
				m_TilesToDraw[index].texCoords = BottomLeft;
				index++;
				
			}
}

//calcs the Tile size in the image 
const sf::Vector2i TilemapReader::CalcTileSizeInImage(const sf::Vector2i& ImageTiling)
{
	return {
		static_cast<int>(m_TilesetTexture.getSize().x / ImageTiling.x),
		static_cast<int>(m_TilesetTexture.getSize().y / ImageTiling.y)
	};
}

//calculates the image rect of a index 0 is {0, 0, width, height} on the image
const sf::IntRect TilemapReader::calcRectOfIndexNumber(const unsigned int index, const sf::Vector2i& ImageTiling, const sf::Vector2i& TileSizeInImage)
{
	sf::Vector2i Start = {
		static_cast<int>(index % ImageTiling.x) * TileSizeInImage.x,
		static_cast<int>(index / ImageTiling.x) * TileSizeInImage.y
	};

	return sf::IntRect(Start, TileSizeInImage);
}


//resizes the tiles vector and sets the default values
void TilemapReader::resizeTiles(const sf::Vector2i& MapSize, const sf::Vector2u& WindowSize)
{
	m_TileSize.x = static_cast<float>(WindowSize.x) / MapSize.x;
	m_TileSize.y = static_cast<float>(WindowSize.y) / MapSize.y;

	m_Tiles.resize(MapSize.x);

	for (size_t i = 0; i < m_Tiles.size(); i++)
		m_Tiles[i].resize(MapSize.y, { {-1}, true });
}

//drawing 
void TilemapReader::draw(sf::RenderTarget& window, sf::RenderStates state) const
{
	window.draw(m_TilesToDraw, &m_TilesetTexture);
}
