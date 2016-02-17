#pragma once
#include "Core/BaseState.h"
class EventData;

class State_MainMenu : public BaseState
{
public:
	State_MainMenu(StateManager* stateManager);
	~State_MainMenu();

	void toIntro(EventData* data);

	// Inherited via BaseState
	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void activate() override;

	virtual void deactivate() override;

	virtual void update(const sf::Time & delta) override;

	virtual void render() override;

private:
	sf::Font font;
	sf::Text text;
};

