#pragma once
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <functional>
#include "StateManager.h"

enum class Event {
	Closed = sf::Event::Closed,
	Resized = sf::Event::Resized,
	LostFocus = sf::Event::LostFocus,
	GainedFocus = sf::Event::GainedFocus,
	TextEntered = sf::Event::TextEntered,
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MouseWheelMoved = sf::Event::MouseWheelMoved,
	MouseWheelScrolled = sf::Event::MouseWheelScrolled,
	MouseButtonDown = sf::Event::MouseButtonPressed,
	MouseButtonUp = sf::Event::MouseButtonReleased,
	MouseMoved = sf::Event::MouseMoved,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	JoystickButtonDown = sf::Event::JoystickButtonPressed,
	JoystickButtonUp = sf::Event::JoystickButtonReleased,
	JoystickMoved = sf::Event::JoystickMoved,
	JoystickConnected = sf::Event::JoystickConnected,
	JoystickDisconnected = sf::Event::JoystickDisconnected,

	// Custom events
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

// Holds the code for the key we're interested in
// i.e the code for the key, mouse button, etc
struct EventInfo {
	EventInfo() { code = 0; }
	EventInfo(int info) { code = info; }
	union { // Unions store only its most recently modified member
		int code;
	};
};

// ...
struct EventData {
	EventData(const std::string& name)
		: name(name)
	{
		clear();
	}

	void clear()
	{
		size = sf::Vector2i(0, 0);
		textEntered = 0;
		mouse = sf::Vector2i(0, 0);
		mouseWheelDelta = 0;
		keyCode = -1;
	}

	std::string name;
	sf::Vector2i size;
	sf::Uint32 textEntered;
	sf::Vector2i mouse;
	int mouseWheelDelta;
	int keyCode;
};

using Events = std::vector< std::pair<Event, EventInfo> >;
struct Binding {
	Binding(const std::string& name)
		: name(name), data(name), count(0)
	{
	}

	void bindEvent(Event event, EventInfo info = EventInfo())
	{ // i.e. bindEvent(Event::KeyDown, Key::A)
		events.emplace_back(event, info);
	}

	Events events;
	EventData data;
	std::string name;
	int count;
};

using Bindings = std::unordered_map<std::string, Binding*>;


using CallbackContainer = std::unordered_map< std::string, std::function<void(EventData*)> >;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool addBinding(Binding* binding);
	void removeBinding(const std::string& name);
	void setFocus(bool focus);
	void setState(StateType type);

	template<class T>
	bool addCallback(StateType type, const std::string& name, void(T::*func)(EventData*), T* instance)
	{
		m_callbacks.emplace(std::make_pair(type, CallbackContainer()));
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return m_callbacks[type].emplace(name, temp).second;
	}

	void removeCallback(const std::string& name)
	{
		m_callbacks[m_state].erase(name);
	}

	void handleEvent(sf::Event& event);
	void update();

	sf::Vector2i getMousePos(sf::RenderWindow* window = nullptr);

private:
	void loadBindings();

	Bindings m_bindings;
	Callbacks m_callbacks;
	StateType m_state;
	bool m_hasFocus;
};