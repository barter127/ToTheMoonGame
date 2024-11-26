#pragma once

#include <sstream>

// Add interactivity through more randomness and some drastic changes.

extern bool inEvent;
extern short eventDays;

void RollEvent();

void EventGainMoney();
void EventLoseMoney();

void EventGainAsset();
void EventLoseAsset();

void SetMarketForecast(bool isRising);
void SetMarketForecast(bool isRising);

void EventMarketFall();
void EventMarketRise();

void DisplayCustomTextbox(std::ostringstream& msg, const std::wstring& title);

void MarketHint();

inline void UpdateEventDays()
{
	if (eventDays > 0)
		eventDays--;

	else if (inEvent)
		inEvent = false;
}