#pragma once

//An emun for all the possible actions in the game

enum class ActionEnum:int {
	NOACTION = 0,
	LEFT,
	RIGHT,
	FORWARD,
	BACK,
	RAISE,
	LOWER,
	RESET,
	LATER,
	EARLIER,
	CREATE,
	DESTROY,
};

/* This struct deals with an agent creating events.  This has an agent number and the action*/
struct gameEvent
{
	int agent;
	ActionEnum action;
};

