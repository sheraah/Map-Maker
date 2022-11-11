#pragma once
#include<map>
#include<SFML/Graphics.hpp>
#include<Windows.h>

//less writing :)
typedef sf::Keyboard::Key Key;


class InputHandler
{
public:
	enum InputMode { NotLoop, Loop };

private:

	//Data of every key
	struct KeyData
	{
		bool m_CanBePessed = true;
	};


	//member variables
	std::map<std::vector<Key>, KeyData> m_Keys;

	static InputHandler& getInstance();

public:

	static bool isPressed(const std::vector<Key>& Keys, const InputMode& Mode);
	static bool isPressed(const Key& KeyToCheck, const InputMode& Mode);
};

