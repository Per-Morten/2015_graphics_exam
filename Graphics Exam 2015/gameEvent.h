#pragma once
#include <queue>
#include <map>

enum class ActionEnum:int {
	NOACTION = 0,
	LEFT,
	RIGHT,
	FORWARD,
	BACK,
	RAISE,
	LOWER,
	LATER,
	EARLIER,
	CREATE,
	DESTROY,
};



class gameEvent
{
public:
	gameEvent(ActionEnum action);
	~gameEvent();
	int agent;
	ActionEnum action;
};

