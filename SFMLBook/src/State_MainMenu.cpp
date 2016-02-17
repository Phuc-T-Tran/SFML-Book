#include "State_MainMenu.h"
#include "Core/StateManager.h"
#include "Core/Window.h"
#include <iostream>
#include "Core\EventManager.h"

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

	// Add state hotkeys
	Binding* binding = new Binding("toIntro");
	binding->bindEvent(Event::Keyboard, 28);
	m_stateManager->getContext()->eventManager->addBinding(binding);
	m_stateManager->getContext()->eventManager->addCallback(StateType::MainMenu, "toIntro", &State_MainMenu::toIntro, this);

	std::cout << "MainMenu Created" << std::endl;
}

void State_MainMenu::onDestroy()
{
	m_stateManager->getContext()->eventManager->removeBinding("toIntro");
	m_stateManager->getContext()->eventManager->removeCallback("toIntro");
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

void State_MainMenu::toIntro(EventData* data)
{
	m_stateManager->switchTo(StateType::Intro);
}
