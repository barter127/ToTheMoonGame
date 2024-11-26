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

const int MAX_MONEY_ROLL = 10'000;
const int MAX_ASSET_ROLL = 1000;

const int MAX_WEIGHT = 25;
const int MAX_TREND_DAYS = 20;

// Event pre-fix so not misused.

// Better timer intermingeling.
// Randomised Msgs.

// unique lock
// string array.
// Fix £ sign.

// Could of created a range but it's really funny to get a notif for an increase of just 1.

// Array of func ptrs. Simply just add new events here.
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
	int randNum = rand() % 100;

	// Could be optimised as array doesn't change size.
	int eventAmount = sizeof everntArr / sizeof everntArr[0];

	if (randNum < eventAmount)
	{
		everntArr[randNum]();
	}
} 

// Increase Money
void EventGiveMoney()
{
	timerOn = false;

	int amount = rand() % MAX_MONEY_ROLL + 1;

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

	int amount = rand() % MAX_MONEY_ROLL + 1;

	// Cap decrease.
	if (money < amount)
		amount = money;

	std::stringstream msg;
	msg << "Your oven broke. The cost for reapirs are £" << amount;
	std::string msgString = msg.str();
	std::wstring msgW(msgString.begin(), msgString.end());

	MessageBox(NULL, msgW.c_str(), L"Event!", MB_OK);

	money -= amount;

	timerOn = true;
}

// Increase Asset Owned
void EventGainAsset()
{
	timerOn = false;
	int amount = rand() % MAX_ASSET_ROLL + 1;

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

	int amount = rand() % MAX_ASSET_ROLL + 1;

	// Cap decrease.
	if (assetOwned < amount)
		amount = assetOwned;

	std::stringstream msg;
	msg << amount << " of your doughnuts ... TURNED OUT TO BE BAGELS.";
	std::string msgString = msg.str();
	std::wstring msgW(msgString.begin(), msgString.end());

	MessageBox(NULL, msgW.c_str(), L"Event!", MB_OK);

	assetOwned -= amount;

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
	eventDays =  rand() % MAX_TREND_DAYS + 1;
	rngWeight = rand() % MAX_WEIGHT; + 1;

	timerOn = true;
}