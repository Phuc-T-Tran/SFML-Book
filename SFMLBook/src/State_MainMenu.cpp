#include "State_MainMenu.h"
#include "Core/StateManager.h"
#include "Core/Window.h"
#include <iostream>


State_MainMenu::State_MainMenu(StateManager* stateManager)
	: BaseState(stateManager)
{
}


State_MainMenu::~State_MainMenu()
{
}

void State_MainMenu::onCreate()
{
	font.loadFromFile("data/fonts/consola.ttf");
	sf::Text text("MENU", font, 55);
	this->text = text;
	this->text.setPosition(300, 300);
	this->text.setColor(sf::Color::White);

	std::cout << "MainMenu Created" << std::endl;
}

void State_MainMenu::onDestroy()
{
}

void State_MainMenu::activate()
{
	std::cout << "MainMenu Activated" << std::endl;
}

void State_MainMenu::deactivate()
{
	std::cout << "MainMenu Deactivated" << std::endl;
}

void State_MainMenu::update(const sf::Time & delta)
{
}

void State_MainMenu::render()
{
	m_stateManager->getContext()->window->draw(text);
}
