#include "State_Intro.h"
#include "Core/StateManager.h"
#include "Core/Window.h"
#include <iostream>
#include "Core\EventManager.h"


State_Intro::State_Intro(StateManager* stateManager)
	: BaseState(stateManager)
{
}


State_Intro::~State_Intro()
{
	onDestroy();
}

void State_Intro::toMainMenu(EventData* data)
{
	m_stateManager->switchTo(StateType::MainMenu);
}

void State_Intro::onCreate()
{
	// Configure background
	backgroundTexture.loadFromFile("data/textures/bg_snowy.png");
	background.setTexture(backgroundTexture);

	// Configure intro text
	font.loadFromFile("data/fonts/consola.ttf");
	sf::Text text("INTRO", font, 55);
	this->text = text;
	this->text.setPosition(100, 100);
	this->text.setColor(sf::Color::White);

	// Add state hotkeys
	m_stateManager->getContext()->eventManager->addCallback(StateType::Intro, "toMainMenu", &State_Intro::toMainMenu, this);

	std::cout << "Intro Created" << std::endl;
}

void State_Intro::onDestroy()
{
	m_stateManager->getContext()->eventManager->removeCallback("toMainMenu");
	std::cout << "Intro Destroyed" << std::endl;
}

void State_Intro::activate()
{
	std::cout << "Intro Activated" << std::endl;
}

void State_Intro::deactivate()
{
	std::cout << "Intro Deactivated" << std::endl;
}

void State_Intro::update(const sf::Time & delta)
{
}

void State_Intro::render()
{
	m_stateManager->getContext()->window->draw(background);
	m_stateManager->getContext()->window->draw(text);
}
