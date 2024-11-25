#include "Events.h"

#include <Windows.h>
#include <sstream>

// Player statistics.
extern double money;
extern unsigned int assetOwned;
extern float assetPrice;
extern unsigned int day;

extern bool timerOn;

extern bool rngWeight;

// Event pre-fix so not misused.

// Increase Money
void EventGiveMoney()
{
	timerOn = false;
	std::wstring msg = L"You found money!";

	MessageBox(NULL, msg.c_str(), L"Event!", MB_OK);
	money += 1000;

	timerOn = true;
}

// Decrease Money
void EventLoseMoney()
{
	timerOn = false;
	std::wstring msg = L"You're oven broke. Pay for repairs :(";

	MessageBox(NULL, msg.c_str(), L"Event!", MB_OK);

	// Cap decrease.
	if (money >= 1000) 
		money -= 1000;
	else
		money = 0;

	timerOn = true;
}

// Increase Asset Owned
void EventGainAsset()
{
	timerOn = false;
	std::wstring msg = L"You were accidentally given a bakers dozen!";

	MessageBox(NULL, msg.c_str(), L"Event!", MB_OK);

	assetOwned += 100;

	timerOn = true;
}

// Decrease Asset Owned
void EventLoseAsset()
{
	timerOn = false;
	std::wstring msg = L"You were accidentally given a bakers dozen";

	MessageBox(NULL, msg.c_str(), L"Event!", MB_OK);

	if (assetOwned >= 100)
		assetOwned -= 100;
	else
		assetOwned = 0;

	timerOn = true;
}

// Stocks will fall

// Stocks will rise.