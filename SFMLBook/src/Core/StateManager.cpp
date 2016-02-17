#include "StateManager.h"
#include "../State_Intro.h"
#include "../State_MainMenu.h"
#include "EventManager.h"
#include <iostream>
#include "Window.h"

StateManager::StateManager(Context* context)
	: m_context(context)
{
	registerState<State_Intro>(StateType::Intro);
	registerState<State_MainMenu>(StateType::MainMenu);
	//registerState<State_Intro>(StateType::Intro);
	//registerState<State_Intro>(StateType::Intro);
}


StateManager::~StateManager()
{
	for (auto& it : m_states)
	{
		it.second->onDestroy();
		delete it.second;
		it.second = nullptr;
	}
}

void StateManager::update(const sf::Time& delta)
{
	if (m_states.empty()) { return; }
	
	// Move the iterator back until we aren't transcendent
	auto it = m_states.end()-1;
	while (it != m_states.begin())
	{
		if ((*it).second->isTranscendent())
			it--;
		else
			break;
	}

	// Update the states from the bottom up
	for (; it != m_states.end(); it++)
		(*it).second->update(delta);
}

void StateManager::render()
{
	if (m_states.empty()) { return; }
	
	// Move the iterator back until we aren't transparent
	auto it = m_states.end() - 1;
	while (it != m_states.begin())
	{
		if ((*it).second->isTransparent())
			it--;
		else
			break;
	}

	// Render the states from the bottom up
	for (; it != m_states.end(); it++)
	{
		m_context->window->getRenderWindow().setView((*it).second->m_view);
		(*it).second->render();
	}
}

void StateManager::processRequests()
{
	for (auto it = m_toRemove.begin(); it != m_toRemove.end(); it++)
	{
		removeState(*it);
		m_toRemove.erase(it);
	}
}

Context* StateManager::getContext()
{
	return m_context;
}

bool StateManager::hasState(const StateType& type)
{
	if (m_states.empty())
		return false;

	for (auto& it : m_states)
	{
		if (it.first == type)
			return true;
	}
}

void StateManager::switchTo(const StateType& type)
{
	m_context->eventManager->setState(type);
	for (auto it = m_states.begin(); it != m_states.end(); it++)
	{
		if ((*it).first == type)
		{
			m_states.back().second->deactivate();
			BaseState* tempState = (*it).second;
			m_states.erase(it);
			m_context->window->getRenderWindow().setView(tempState->m_view);
			m_states.emplace_back(std::make_pair(type, tempState));
			return;
		}
	}

	if (m_states.size() > 0)
		m_states.back().second->deactivate();

	createState(type);
	m_context->window->getRenderWindow().setView(m_states.back().second->m_view);
	m_states.back().second->activate();
}

void StateManager::remove(const StateType& type)
{
	m_toRemove.push_back(type);
}

void StateManager::createState(const StateType& type)
{
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end()) { return; }

	BaseState* state = newState->second();
	state->m_view = m_context->window->getRenderWindow().getView();
	
	m_states.emplace_back(type, state);
	state->onCreate();
}
void StateManager::removeState(const StateType& type)
{
	for (auto it = m_states.begin(); it != m_states.end(); it++)
	{
		if ((*it).first == type)
		{
			delete (*it).second;
			m_states.erase(it);
			return;
		}
	}
}