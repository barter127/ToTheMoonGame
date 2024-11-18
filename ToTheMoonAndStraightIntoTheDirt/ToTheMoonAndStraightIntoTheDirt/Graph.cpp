#include "Graph.h"
#include <iostream>
#include <string>
#include <sstream>

std::ostringstream buffer;

void DrawGraphBuffer()
{
    std::string bufferString = buffer.str();
    std::cout << bufferString;

    buffer.str("");
    buffer.clear();
}

void DrawYAxisLabel(int graphHeight)
{
    // Draw
    if ((graphHeight * 2) % 5 == 0)
    {
        // Display graph numbers.
        buffer << graphHeight * 2 << "-";
    }
    else buffer << "   ";

    // Draw seperator. 
    buffer << "|";
}

void DrawMarketTrend(short fluctuation)
{
    switch (fluctuation)
    {
        case 1:
            buffer << "/";
            break;
        case 0:
            buffer << "_";
            break;
        case -1:
            buffer << "\\";
    }
}

void DrawWhiteSpace()
{
    buffer << " ";
}

// I believe the trade off of having these not be inline is better than iostream in the header.
void NewLine()
{
    buffer << "\n";
}

float RandomRange(int lowest, int highest)
{
    int range = (highest - lowest) + 1;
    return (rand() % range) + lowest; // Problematic if lowest is >0. 
}