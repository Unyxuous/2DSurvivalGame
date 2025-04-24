#pragma once

#include "Click.h"
#include "Player.h"
#include "World.h"

class Player;

class PlayerState
{
protected:
	bool canJump(Player&);
public:
	virtual ~PlayerState();
	virtual void manageInput(sf::RenderWindow&, sf::View,Player&)=0;
	virtual void update(Player&)=0;
};

class IdleState : public PlayerState {
	void manageInput(sf::RenderWindow&, sf::View,Player&);
	void update(Player&);
	~IdleState();
};

class WalkState : public PlayerState {
	void manageInput(sf::RenderWindow&, sf::View,Player&);
	void update(Player&);
	~WalkState();
};

class JumpState : public PlayerState {
	void manageInput(sf::RenderWindow&, sf::View,Player&);
	void update(Player&);
	~JumpState();
};