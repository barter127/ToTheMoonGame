#include <chrono>
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <map>
#include <functional>

#include "Start+End.h"
#include "Graph.h"
#include "Commands.h"

// 480 bytes
short marketGraph[116][2];

void Timer();
void NextDay();
inline void SetSeed();

static bool timerOn = true; 


int main()
{
    int rngWeight = 0;

    // Set console colour. BG: Black, Text: Green
    system("Color 0A");

    //PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE DON'T FORGET TO UNCOMMENT THIS
    //DisplayTitle();

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

void Timer()
{
    using namespace std::chrono_literals;

    timerOn = true;

    while (timerOn) // Having it sleep causes delay on exit.
    {
        std::this_thread::sleep_for(3s);

        NextDay();
    }
}

void NextDay()
{
    // Clear console.
    system("cls"); // Not clearing looks more seamless but I prefer this over scrolling through console.

    UpdateMarket(marketGraph);
    BufferGraph(marketGraph);
    DrawGraphBuffer();

    std::cout << "> Current price: " << assetPrice << "\n";
    std::cout << "> Money: " << money << "\n";
    std::cout << lastCommandOutput << "\n";
}

inline void SetSeed()
{
    srand(time(NULL));
}