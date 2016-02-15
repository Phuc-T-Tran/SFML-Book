#include "StateManager.h"



StateManager::StateManager(Context* context)
	: m_context(context)
{
}


StateManager::~StateManager()
{
}

void StateManager::update(const sf::Time& delta)
{
	m_states.front().second->update(delta);
}

void StateManager::render()
{

}

void StateManager::processRequests()
{

}

Context* StateManager::getContext()
{

}
bool StateManager::hasState(const StateType& type)
{

}
void StateManager::switchTo(const StateType& type)
{

}
void StateManager::remove(const StateType& type)
{

}
void StateManager::createState(const StateType& type)
{

}
void StateManager::removeState(const StateType& type)
{

}