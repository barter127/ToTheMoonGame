#include "Graph.h"
#include <iostream>

void EraseGraph()
{
    printf("\033[%d;%dH", 1, 1);

    // +1 for current price line
    int graphHeight = (GRAPH_TOP / Money_Multiplier) + 1;

    for (int i = 0; i < graphHeight; i++)
    {
        printf("\x1b[2K");
        std::cout << "\n";
    }
}

void DrawYAxisLabel(int graphHeight)
{
    // Draw
    if ((graphHeight * 2) % 5 == 0)
    {
        // Display graph numbers.
        std::cout << graphHeight * 2 << "-";
    }
    else std::cout << "   ";

    // Draw seperator. 
    std::cout << "|";
}

void DrawMarketTrend(short fluctuation)
{
    switch (fluctuation)
    {
        case 1:
            std::cout << "/";
            break;
        case 0:
            std::cout << "_";
            break;
        case -1:
            std::cout << "\\";
    }
}

void DrawWhiteSpace()
{
    std::cout << " ";
}

// I believe the trade off of having these not be inline is better than iostream in the header.
void NewLine()
{
    // Printf supposed to be a lot quicker when just making a new line.
    printf("\n");
}

float RandomRange(int lowest, int highest)
{
    int range = (highest - lowest) + 1;
    return (rand() % range) + lowest; // Problematic if lowest is >0. 
}