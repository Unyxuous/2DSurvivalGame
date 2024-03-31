#pragma once

#include "Player.h"
//needed for breaking/placing blocks
#include "World.h"

class Player;

class PlayerState
{
public:
	virtual ~PlayerState();
	virtual void manageInput(sf::RenderWindow&, World&, Player&)=0;
	virtual void update(Player&)=0;
};

class IdleState : public PlayerState {
	void manageInput(sf::RenderWindow&, World&, Player&);
	void update(Player&);
	~IdleState();
};

class WalkState : public PlayerState {
	void manageInput(sf::RenderWindow&, World&, Player&);
	void update(Player&);
	~WalkState();
};

class JumpState : public PlayerState {
	void manageInput(sf::RenderWindow&, World&, Player&);
	void update(Player&);
	~JumpState();
};