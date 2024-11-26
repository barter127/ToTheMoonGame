#pragma once

// Add interactivity through more randomness and some drastic changes.

extern bool inEvent;
extern short eventDays;

void RollEvent();

void EventGiveMoney();
void EventLoseMoney();

void EventGainAsset();
void EventLoseAsset();

void EventMarketFall();
void EventMarketRise();

inline void UpdateEventDays()
{
	if (eventDays > 0)
		eventDays--;

	else if (inEvent)
		inEvent = false;
}