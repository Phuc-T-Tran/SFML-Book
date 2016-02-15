#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>

class StateManager;
class Window;
class EventManager;

enum class StateType { None, Intro, MainMenu, Game, Paused, GameOver, Credits };

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

struct Context {
	Context() : m_window(nullptr), m_eventManager(nullptr) {}
	Window* m_window;
	EventManager* m_eventManager;
};

class BaseState
{
public:
	BaseState(StateManager* stateManager)
		: m_stateManager(stateManager), m_transparent(false), m_transcendent(false)
	{
	}

	virtual ~BaseState() {}

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void active() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time& delta) = 0;
	virtual void render() = 0;

	void setTransparent(bool transparent) { m_transparent = transparent; }
	void setTranscendent(bool transcendent) { m_transparent = transcendent; }

	bool isTransparent() { return m_transparent; }
	bool isTranscendent() { return m_transcendent; }

protected:
	StateManager* m_stateManager;
	bool m_transparent;  // Render state beneath us
	bool m_transcendent; // Update state beneath us
};

