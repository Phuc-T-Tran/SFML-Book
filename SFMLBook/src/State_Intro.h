#pragma once
#include "Core/BaseState.h"
class EventData;

class State_Intro : public BaseState
{
public:
	State_Intro(StateManager* stateManager);
	~State_Intro();

	void toMainMenu(EventData* data);

	// Inherited via BaseState
	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void activate() override;

	virtual void deactivate() override;

	virtual void update(const sf::Time & delta) override;

	virtual void render() override;

private:
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Font font;
	sf::Text text;
};

