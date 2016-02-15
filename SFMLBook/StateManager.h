#pragma once
#include "BaseState.h"

class StateManager {
public:
	StateManager(Context* context);
	~StateManager();
	void update(const sf::Time& delta);
	void render();
	void processRequests();
	Context* getContext();
	bool hasState(const StateType& type);
	void switchTo(const StateType& type);
	void remove(const StateType& type);

private:
	void createState(const StateType& type);
	void removeState(const StateType& type);
	template<class T>
	void registerState(const StateType& type)
	{
	}
	
	Context* m_context;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};