#include <chrono>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <sstream>
#include <map>
#include <functional>

#include "Start+End.h"
#include "Graph.h"
#include "Commands.h"

#include "Events.h"

#define TWO_DP std::fixed << std::setprecision(2)

// 480 bytes
// With index being position on x value stored at [x][0] being position y and value stored at [x][1] is fluctuation.
short marketGraph[116][2];

// Player statistics.
double money = 2500; // Needs negative values for possible debt mechanic.
unsigned int assetOwned = 0;
float assetPrice = 25.0;
unsigned int day = 1; // May be problematic for long play sessions.

bool timerOn = true; 

void Timer();
void NextDay();
inline void SetSeed();

std::mutex m;
std::condition_variable cv;

int main()
{
    // Set console colour. BG: Black, Text: Green
    system("Color 0A");

    DisplayTitle();

    SetSeed();

    IntialiseGraph(marketGraph);
    NextDay();
   
    // Start Threads.
    std::thread Countdown(Timer);

    // Game loop
    while (!endGame)
    {
        GetCommand();
        std::cout << lastCommandOutput << "\n";
    }

    // Game end
    Countdown.join();

    PrintEndStats();
    std::cout << "\n";
    PrintEndGameMessage();
}

// Is always active in some way.
// Basically the beating heart of the program. It deserves to be in main.
void Timer()
{
    using namespace std::chrono_literals;

    // PLEASE UPDATE THIS I WILL CRY.
    while (true) // Having it sleep causes delay on exit.
    {
        std::this_thread::sleep_for(3s);

        if (timerOn)
        {
            NextDay();
        }

    }
}

void DisplayPriceSummary()
{
    // Print two DP to match money standards.
    std::cout << "> Current price: " << TWO_DP << assetPrice << "\n";
    std::cout << "> Money: " << TWO_DP << money << "\n";
    std::cout << lastCommandOutput << "\n";
}

// Update nessecary variables. Redraw graph.
void NextDay()
{
    day++;
    UpdateEventDays();
    RollEvent();

    // Clear console.
    system("cls"); // Not clearing looks more seamless but I prefer this over scrolling through console.

    UpdateMarket(marketGraph);
    BufferGraph(marketGraph);
    DrawGraphBuffer();

    DisplayPriceSummary();
}

// Is this pointless? A bit, but the code inside is ugly. This adds clarity.
inline void SetSeed()
{
    srand(time(NULL));
}
