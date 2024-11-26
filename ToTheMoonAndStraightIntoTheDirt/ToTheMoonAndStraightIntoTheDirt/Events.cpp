#include "Events.h"

#include <Windows.h>
#include <sstream>
#include <functional>

// Player statistics.
extern double money;
extern unsigned int assetOwned;
extern float assetPrice;
extern unsigned int day;

// Main.cpp
extern bool timerOn;

// Graph.cpp
extern int rngWeight;

bool inEvent = false;
short eventDays = 0;

// Event pre-fix so not misused.

// randomised vars + output in window.
// Better timer intermingeling.
// Randomised Msgs.

// Wstringstream
// unique lock
// string array.
// Fix £ sign.

// Could of created a range but it's really funny to get a notif for an increase of just 1.

// Array of func ptrs.
std::function<void()> everntArr[] = {
	EventGiveMoney,
	EventLoseMoney,
	EventGainAsset,
	EventLoseAsset,
	EventMarketFall,
	EventMarketRise
};

void RollEvent()
{
	// rool 1 - 1000

	int randNum = rand() % 100;

	// Could be optimised as array doesn't change size.
	int eventAmount = sizeof everntArr / sizeof everntArr[0];

	if (randNum < eventAmount)
	{
		everntArr[randNum];
	}
	int hi = 0;
	// GRAPH CAN STILL GO OUT OF BOUNDS!!!
}

// Increase Money
void EventGiveMoney()
{
	timerOn = false;

	int amount = rand() % 10'000;

	std::stringstream msg;
	msg << "You found £" << amount << ". Good on you :)"; 
	std::string msgString = msg.str();
	std::wstring msgW(msgString.begin(), msgString.end());

	MessageBox(NULL, msgW.c_str(), L"Event!", MB_OK);

	money += amount;

	timerOn = true;
}

// Decrease Money
void EventLoseMoney()
{
	timerOn = false;

	int amount = rand() % 10'000;

	std::stringstream msg;
	msg << "Your oven broke. The cost for reapirs are £" << amount;
	std::string msgString = msg.str();
	std::wstring msgW(msgString.begin(), msgString.end());

	MessageBox(NULL, msgW.c_str(), L"Event!", MB_OK);

	// Cap decrease.
	if (money >= amount) 
		money -= amount;
	else
		money = 0;

	timerOn = true;
}

// Increase Asset Owned
void EventGainAsset()
{
	timerOn = false;
	int amount = rand() % 1000;

	std::stringstream msg;
	msg << "You got given a bakers dozen! +" << amount << " doughnuts";
	std::string msgString = msg.str();
	std::wstring msgW(msgString.begin(), msgString.end());

	MessageBox(NULL, msgW.c_str(), L"Event!", MB_OK);

	assetOwned += amount;

	timerOn = true;
}

// Decrease Asset Owned
void EventLoseAsset()
{
	timerOn = false;

	int amount = rand() % 1000;

	std::stringstream msg;
	msg << amount << " of your doughnuts ... TURNED OUT TO BE BAGELS.";
	std::string msgString = msg.str();
	std::wstring msgW(msgString.begin(), msgString.end());

	MessageBox(NULL, msgW.c_str(), L"Event!", MB_OK);

	if (assetOwned >= amount)
		assetOwned -= amount;
	else
		assetOwned = 0;

	timerOn = true;
}

// Stocks will fall
void EventMarketFall()
{
	timerOn = false;
	std::wstring msg = L"THE MARKET WILL BE CRIPPLED >:D";

	MessageBox(NULL, msg.c_str(), L"Event!", MB_OK);

	inEvent = true;
	eventDays = 10;
	rngWeight = -10;

	timerOn = true;
}

// Stocks will rise.
void EventMarketRise()
{
	timerOn = false;
	std::wstring msg = L"THE MARKET IS BOOMING! :D";

	MessageBox(NULL, msg.c_str(), L"Event!", MB_OK);

	inEvent = true;
	eventDays = 10;
	rngWeight = 10;

	timerOn = true;
}