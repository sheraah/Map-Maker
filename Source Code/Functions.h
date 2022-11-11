#pragma once
#include "InputHandler.h"

const sf::Vector2u DebugRes = { 1500, 1000 };

//Some useful functions
class Functions
{
private:
	//member variables
	sf::RenderWindow* m_WindowRef;

	sf::Text m_Text;
	sf::Font m_Font;


	static Functions& getInstance()
	{
		static Functions ins;
		return ins;
	}

public:
	Functions();
	Functions(const Functions& other) = delete;

	static void init(sf::RenderWindow* winodowRef);

	static std::string OpenFile(const char* Filter);

	static void drawText(sf::RenderWindow* window, const std::string& str, const sf::Vector2f& pos, const float& chSize, const sf::Color& color);
	static void setFont(const std::string& FontPath);

	template <typename T>
	static T clamp(const T& value, const T& min, const T& max) { return std::max(min, std::min(value, max)); }

	template<typename T>
	static std::string ArrayToString(const std::vector<T>& vec);


	static std::string getProjectDirectory();

	static const sf::Vector2f CalcVec(const sf::Vector2f& Vec);
	static const sf::Vector2f CalcScale();
	static std::string BoolToText(const bool b) { return b ? "True" : "False"; }
	static sf::Color BoolToColor(const bool b, const sf::Uint8 alpha) { return b ? sf::Color::Color(0, 255, 0, alpha) : sf::Color::Color(255, 0, 0, alpha); }
};
