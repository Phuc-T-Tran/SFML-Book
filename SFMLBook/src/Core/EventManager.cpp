#include "EventManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

EventManager::EventManager() : m_hasFocus(true)
{
	loadBindings();
}

EventManager::~EventManager()
{
	for (auto& itr : m_bindings)
	{
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::addBinding(Binding* binding)
{
	if (m_bindings.find(binding->name) != m_bindings.end())
	{
		std::cout << "Binding " + binding->name + " already exists." << std::endl;
		return false;
	}

	m_bindings.emplace(binding->name, binding);
	return true;
}

void EventManager::removeBinding(const std::string& name)
{
	if (m_bindings.find(name) != m_bindings.end())
	{
		delete (*(m_bindings.find(name))).second;
		m_bindings.erase(name);
	}
}

void EventManager::setFocus(bool focus)
{
	m_hasFocus = focus;
}

void EventManager::setState(StateType type)
{
	m_state = type;
}

void EventManager::handleEvent(sf::Event& event)
{
	for (auto& b_it : m_bindings)
	{
		Binding* binding = b_it.second;
		for (auto& e_it : binding->events)
		{
			Event sfmlEvent = (Event)event.type;
			if (sfmlEvent == e_it.first) // The event that is happening is bound
			{
				// If keyboard or mouse event, we have to also check that the key/button
				// matches the one for our binding
				if (sfmlEvent == Event::KeyDown ||
					sfmlEvent == Event::KeyUp)
				{
					if (e_it.second.code == event.key.code)
					{
						binding->count++;
						if (binding->data.keyCode != -1)
							binding->data.keyCode = e_it.second.code;
						break;
					}
				}
				else if (sfmlEvent == Event::MouseButtonDown ||
					sfmlEvent == Event::MouseButtonUp)
				{
					if (e_it.second.code == event.mouseButton.button)
					{
						binding->count++;
						binding->data.mouse.x = event.mouseButton.x;
						binding->data.mouse.y = event.mouseButton.y;
						if (binding->data.keyCode == -1)
							binding->data.keyCode = e_it.second.code;
						break;
					}
				}
				else // Seperated because we do not need to check for specifics
				{
					if (sfmlEvent == Event::MouseWheelMoved) { // || event.MouseWheelScrolled??
						binding->data.mouseWheelDelta = event.mouseWheel.delta;
					}
					else if (sfmlEvent == Event::Resized) {
						binding->data.size.x = event.size.width;
						binding->data.size.y = event.size.height;
					}
					else if (sfmlEvent == Event::TextEntered) {
						binding->data.textEntered = event.text.unicode;
					}
					binding->count++;
					break;
				}
			}
		}
	}
}

void EventManager::update()
{
	if (!m_hasFocus)
		return;

	for (auto& b_it : m_bindings)
	{
		Binding* binding = b_it.second;
		for (auto& e_it : binding->events)
		{
			switch (e_it.first)
			{
			case Event::Keyboard:
			{
				if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key(e_it.second.code))))
				{
					if (binding->data.keyCode != -1)
						binding->data.keyCode = e_it.second.code;
					binding->count++;
				}
				break;
			}
			case Event::Mouse:
			{
				if (sf::Mouse::isButtonPressed((sf::Mouse::Button(e_it.second.code))))
				{
					if (binding->data.keyCode != -1)
						binding->data.keyCode = e_it.second.code;
					binding->count++;
				}
				break;
			}
			case Event::Joystick:
			{
				break;
			}
			}
		}
		if (binding->events.size() == binding->count)
		{
			// All events are satisfied. Execute the callback.
			// Check for global callbacks first
			auto gc_it = m_callbacks[StateType::None].find(binding->name);
			if (gc_it != m_callbacks[StateType::None].end())
				(*gc_it).second(&binding->data);
			
			// Then check for state specific callbacks
			auto c_it = m_callbacks[m_state].find(binding->name);
			if (c_it != m_callbacks[m_state].end())
				(*c_it).second(&binding->data);
		}
		binding->count = 0;
		binding->data.clear();
	}
}

sf::Vector2i EventManager::getMousePos(sf::RenderWindow* window)
{
	return (window) ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition();
}

void EventManager::loadBindings() // TODO: Copy pasted.. have a look at this after
{
	std::string delimiter = ":";
	std::ifstream bindings;
	bindings.open("data/cfg/key.cfg");
	if (!bindings.is_open()) {
		std::cout << "Failed loading keys.cfg." << std::endl;
		return;
	}
	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) {
				delete bind;
				bind = nullptr;
				break;
			}
			Event type = Event(stoi(keyval.substr(start, end - start)));
			int code = stoi(keyval.substr(end + delimiter.length(),
				keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.code = code;
			bind->bindEvent(type, eventInfo);
		}
		if (!addBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}