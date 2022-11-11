#include "Functions.h"

//conctructor
Functions::Functions()
	:m_WindowRef(nullptr)
{
	m_Text.setCharacterSize(20);
	m_Text.setFont(m_Font);
}

//init the window
void Functions::init(sf::RenderWindow* winodowRef)
{
	getInstance().m_WindowRef = winodowRef;
}

//Open a file in the explorer and lets the user to select a path and returns it
std::string Functions::OpenFile(const char* Filter) 
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = Filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetOpenFileNameA(&ofn) == TRUE) {
		return ofn.lpstrFile;
	}

	return std::string();
}

//drawText using setScale instead of setCharacterSize is way cheaper :)
void Functions::drawText(sf::RenderWindow* window, const std::string& str, const sf::Vector2f& pos, const float& chSize, const sf::Color& color)
{
	sf::Vector2f WindowScale = CalcScale();
	sf::Vector2f NewScale = {
		chSize / getInstance().m_Text.getCharacterSize() * WindowScale.x,
		chSize / getInstance().m_Text.getCharacterSize() * WindowScale.y
	};

	getInstance().m_Text.setString(str);
	getInstance().m_Text.setPosition(pos);
	getInstance().m_Text.setScale(NewScale);
	getInstance().m_Text.setFillColor(color);

	window->draw(getInstance().m_Text);
}

//set a font for the drawText function
void Functions::setFont(const std::string& FontPath)
{
	getInstance().m_Font.loadFromFile(FontPath);
}

//Converts a Pos from the Debug Res to the current Res
//for example i developed my program in 1500x1000(thats the debug res)
//But what if i have a other resolution?
//if i want to convert { 100, 100 } to the current Resolution for exsample 750x500 
//i need to muliply the components { 100, 100} by the scale is should be { 100 * 0.5f, 100 * 0.5f }
//cuz its the half of the Debug Res
const sf::Vector2f Functions::CalcVec(const sf::Vector2f& Vec)
{
	const sf::Vector2f Scale = CalcScale();

	return { Vec.x * Scale.x, Vec.y * Scale.y};
}

//Calculates the scale of the Debug Res and currnet Resolution
const sf::Vector2f Functions::CalcScale()
{
	const auto& Res = static_cast<sf::Vector2f>(getInstance().m_WindowRef->getSize());

	return { Res.x / DebugRes.x, Res.y / DebugRes.y };
}

//returns the current project directory
std::string Functions::getProjectDirectory()
{
	std::string file{ __FILE__ };

	return { file.substr(0, file.rfind("\\")) };
}