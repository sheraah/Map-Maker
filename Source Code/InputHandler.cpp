#include "InputHandler.h"

//returns a static instance(Singleton)
InputHandler& InputHandler::getInstance()
{
	static InputHandler ins;
	return ins;
}

bool InputHandler::isPressed(const Key& KeyToCheck, const InputMode& Mode)
{
	return isPressed(std::vector<Key>({ KeyToCheck }), Mode);
}

//if the user passes NoyLoop for the mode the functions return true once if the key was pressed
//otherwise(Loop) returns always true while the key is pressed
bool InputHandler::isPressed(const std::vector<Key>& Keys, const InputMode& Mode)
{
	bool Pressed = true;

	for (const auto& k : Keys)
	{
		if (!sf::Keyboard::isKeyPressed(k))
		{
			Pressed = false;
			break;
		}
	}

	if (Mode == InputMode::Loop) return Pressed;

	auto& KeyData = getInstance().m_Keys[Keys];

	if (!Pressed)
	{
		KeyData.m_CanBePessed = true;
	}

	if (Pressed && KeyData.m_CanBePessed)
	{
		KeyData.m_CanBePessed = false;
		return true;
	}

	return false;
}
