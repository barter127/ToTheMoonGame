#pragma once

// Add interactivity through more randomness and some drastic changes.

extern bool inEvent;
extern short eventDays;

void RollEvent();

void EventGiveMoney();
void EventLoseMoney();

void EventGainAsset();
void EventLoseAsset();

// Manipulates Market
void MarketFall();
void MarketRise();

// Just the event.
void EventMarketFall();
void EventMarketRise();


void MarketHint();

inline void UpdateEventDays()
{
	if (eventDays > 0)
		eventDays--;

	else if (inEvent)
		inEvent = false;
}