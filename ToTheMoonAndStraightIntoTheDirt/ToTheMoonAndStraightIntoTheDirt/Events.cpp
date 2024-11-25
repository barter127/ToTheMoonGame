#include "Events.h"

#include <Windows.h>
#include <sstream>

// Player statistics.
extern double money;
extern unsigned int assetOwned;
extern float assetPrice;
extern unsigned int day;

extern bool timerOn;



// Increase Money
void GiveMoney()
{
	timerOn = false;
	std::wstring msg = L"You found money!";

	MessageBox(NULL, msg.c_str(), L"Event!", MB_OK);

	timerOn = true;
}


// Decrease Money

// Increase Asset Owned

// Decrease Asset Owned

// Stocks will fall

// Stocks will rise.