#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>

class StateManager;
class Window;
class EventManager;

class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager* stateManager)
		: m_stateManager(stateManager), m_transparent(false), m_transcendent(false)
	{
	}

	virtual ~BaseState() {}

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time& delta) = 0;
	virtual void render() = 0;

	void setTransparent(bool transparent) { m_transparent = transparent; }
	void setTranscendent(bool transcendent) { m_transparent = transcendent; }

	bool isTransparent() { return m_transparent; }
	bool isTranscendent() { return m_transcendent; }
	sf::View& getView() { return m_view; }

protected:
	StateManager* m_stateManager;
	bool m_transparent;  // Render states beneath us
	bool m_transcendent; // Update states beneath us
	sf::View m_view;
};

