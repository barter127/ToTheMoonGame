#include "Events.h"

#include <Windows.h>
#include <sstream>
#include <functional>
#include <iostream>
#include <iomanip>

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

void RollEvent()
{
	// Array of func ptrs. Simply just add new events here.
	std::function<void()> everntArr[] = {
		EventGiveMoney,
		EventLoseMoney,
		EventGainAsset,
		EventLoseAsset,
		EventMarketFall,
		EventMarketRise,
		MarketHint
	};

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

// Stock will fall.
void MarketFall()
{
	inEvent = true;
	eventDays = rand() % MAX_TREND_DAYS - MAX_TREND_DAYS;
	rngWeight = rand() % MAX_WEIGHT; -MAX_WEIGHT;
}

// Stocks will rise.
void MarketRise()
{
	inEvent = true;
	eventDays = rand() % MAX_TREND_DAYS + 1;
	rngWeight = rand() % MAX_WEIGHT; +1;
}

// Event. (Only difference is the pop-up)
void EventMarketFall()
{
	timerOn = false;
	std::wstring msg = L"THE MARKET SHALL FALL >:D";

	MessageBox(NULL, msg.c_str(), L"Event!", MB_OK);

	MarketFall();

	timerOn = true;
}


// Event. (Only difference is the pop-up)
void EventMarketRise()
{
	timerOn = false;
	std::wstring msg = L"THE MARKET IS BOOMING! :D";

	MessageBox(NULL, msg.c_str(), L"Event!", MB_OK);

	MarketRise();

	timerOn = true;
}

void MarketHint()
{
	// Arbitrary large number.
	if (money > 5000)
	{
		timerOn = false;

		float amount = money * 0.10; // 10%

		std::stringstream msg;
		msg << "Want a market tip? it'll cost you £" << std::fixed << std::setprecision(2) << amount;
		std::string msgString = msg.str();
		std::wstring msgW(msgString.begin(), msgString.end());

		int decision = MessageBox(NULL, msgW.c_str(), L"Psstttt", MB_YESNO);

		if (decision == IDYES)
		{
			money -= amount;

			bool positivePrediction = rand() % 2 == 0;
			bool correctPrediction = rand() % 2 == 0;

			if (positivePrediction)
			{
				MessageBox(NULL, L"The market will SKYROCKET", L"Psstttt", MB_OK);

				if (correctPrediction)
				{
					MarketRise();
				}
				else
				{
					MarketFall();
				}
			}
			else
			{
				MessageBox(NULL, L"The markets in a rough spot. Sell while you can.", L"Psstttt", MB_OK);

				if (correctPrediction)
				{
					MarketRise();
				}
				else
				{
					MarketFall();
				}
			}
		}
		else
			MessageBox(NULL, L"Suit yourself", L"Psstttt", MB_OK);

		timerOn = true;
	}
}