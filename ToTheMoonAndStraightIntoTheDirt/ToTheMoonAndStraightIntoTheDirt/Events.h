#pragma once

extern bool inEvent;
extern short eventDays;

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
	else if (inEvent) // Prevent setting correctly set bool.
		inEvent = false;
}