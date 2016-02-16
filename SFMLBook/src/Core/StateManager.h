#pragma once
#include "BaseState.h"

enum class StateType { None, Intro, MainMenu, Game, Paused, GameOver, Credits, NumStates };

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

struct Context {
	Context() : window(nullptr), eventManager(nullptr) {}
	Window* window;
	EventManager* eventManager;
};

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
		m_stateFactory[type] = //new T(this);
		[this]() -> BaseState* { return new T(this); };
	}
	
	Context* m_context;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};