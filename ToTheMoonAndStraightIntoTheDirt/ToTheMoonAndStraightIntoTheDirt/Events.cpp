#include "Events.h"

#include <Windows.h>
#include <sstream>
#include <functional>
#include <iostream>
#include <iomanip>

#define DP2 std::fixed << std::setprecision(2)

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

// Only used within file.
static const int MAX_MONEY_ROLL = 10'000;
static const int MAX_ASSET_ROLL = 1000;

static const int MAX_WEIGHT = 25;
static const int MAX_TREND_DAYS = 20;

// Event pre-fix so not misused.

// Could of created a range but it's really funny to get a notif for an increase of just 1.
void RollEvent()
{
	// Array of func ptrs. Simply just add new events here.
	std::function<void()> everntArr[] = {
		EventGainMoney,
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

// Increase money
void EventGainMoney()
{
	timerOn = false;

	int amount = rand() % MAX_MONEY_ROLL + 1;

	// Concat Wstring.
	std::ostringstream msg;
	msg << "You found " << amount << ". Good on you :)";

	DisplayCustomTextbox(msg, L"Event!");
	money += amount;

	timerOn = true;
}

// Decrease money.
void EventLoseMoney()
{
	timerOn = false;

	int amount = rand() % MAX_MONEY_ROLL + 1;

	// Cap decrease.
	if (money < amount)
		amount = money;

	// Concat Wstring.
	std::ostringstream msg;
	msg << "Your oven broke. The cost for repairs is " << amount;

	DisplayCustomTextbox(msg, L"Event!");
	money -= amount;

	timerOn = true;
}

void EventGainAsset()
{
	timerOn = false;

	int amount = rand() % MAX_ASSET_ROLL + 1;

	// Concat Wstring.
	std::ostringstream msg;
	msg << "You got given a baker's dozen! +" << amount << " doughnuts";

	DisplayCustomTextbox(msg, L"Event!");
	assetOwned += amount;

	timerOn = true;
}

void EventLoseAsset()
{
	timerOn = false;

	int amount = rand() % MAX_ASSET_ROLL + 1;

	// Cap decrease.
	if (assetOwned < amount)
		amount = assetOwned;

	// Concat Wstring.
	std::ostringstream msg;
	msg << amount << " of your doughnuts ... TURNED OUT TO BE BAGELS.";

	DisplayCustomTextbox(msg, L"Event!");
	assetOwned -= amount;

	timerOn = true;
}

// Group set future logic.
// IDK if it's better grouped. Less clarity but more concise.
void SetMarketForecast(bool isRising)
{
	inEvent = true;
	eventDays = rand() % MAX_TREND_DAYS;
	rngWeight = rand() % MAX_WEIGHT + (isRising ? 1 : -MAX_WEIGHT);
}

void EventMarketRise()
{
	timerOn = false;

	// Concat Wstring.
	std::ostringstream msg;
	msg << "THE MARKET IS BOOMING! :D";

	DisplayCustomTextbox(msg, L"Event!");
	SetMarketForecast(true);

	timerOn = true;
}

void EventMarketFall()
{
	timerOn = false;

	// Concat Wstring.
	std::ostringstream msg;
	msg << "THE MARKET SHALL FALL >:D";

	DisplayCustomTextbox(msg, L"Event!");
	SetMarketForecast(false);

	timerOn = true;
}

void MarketHint()
{
	if (money > 5000)
	{
		timerOn = false;

		float amount = money * 0.10; // 10%

		std::ostringstream msg;
		msg << "Want a market tip? it'll cost you £" << DP2 << amount;

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

				SetMarketForecast(correctPrediction);
			}
			else
			{
				MessageBox(NULL, L"The markets in a rough spot. Sell while you can.", L"Psstttt", MB_OK);

				SetMarketForecast(correctPrediction);
			}
		}
		else
			MessageBox(NULL, L"Suit yourself", L"Psstttt", MB_OK);

		timerOn = true;
	}
}


// Might be worth moving in future. only used here for now so best here.
void DisplayCustomTextbox(std::ostringstream& msg, const std::wstring& title)
{
	// Convert to readable type
	std::string msgString = msg.str();
	std::wstring msgW(msgString.begin(), msgString.end());

	// Messagebox
	MessageBox(NULL, msgW.c_str(), L"Event!", MB_OK);
}