#pragma once
#include <SFML/Graphics.hpp>

class TilemapReader : public sf::Drawable
{
private:
	struct Tile
	{
		std::vector<short> indexes;
		bool collision;
	};

	//member variables
	sf::RenderWindow* m_WindowRef = nullptr;
	sf::Texture m_TilesetTexture;
	sf::Vector2f m_TileSize;
	std::vector<std::vector<Tile>> m_Tiles;
	sf::VertexArray m_TilesToDraw;

	//member functions
	const sf::Vector2i CalcTileSizeInImage(const sf::Vector2i& ImageTiling);
	void resizeTiles(const sf::Vector2i& MapSize, const sf::Vector2u& WindowSize);
	void initVertexArray(const size_t& totalTiles, const sf::Vector2i& ImageTiling, const sf::Vector2i& TileSizeInImage);

	const sf::IntRect calcRectOfIndexNumber(const unsigned int index,const sf::Vector2i& ImageTiling, const sf::Vector2i& TileSizeInImage);

public:
	TilemapReader(const std::string& MapFilePath, sf::RenderWindow* window);
	TilemapReader();
	~TilemapReader() { };

	void init(const std::string& MapFilePath, sf::RenderWindow* window);
	void draw(sf::RenderTarget& window, sf::RenderStates state) const override;
};

