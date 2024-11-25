#include "Graph.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

std::ostringstream buffer;

// Graph vars.
float lastPrice = 12;
int lastGraphHeight = 12;
const int GRAPH_TOP = 25;
const int GRAPH_BOTTOM = 1;
int moneyMultiplier = 2;
int rngWeight = 0;

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
    int coordMarker = graphHeight * moneyMultiplier;
    int markerFrequency = 5 * moneyMultiplier;
    if (coordMarker % markerFrequency == 0)
    {
        // Display graph numbers.
        buffer << graphHeight * moneyMultiplier << "-";
    }
    else buffer << "   ";

    // Draw seperator. 
    buffer << "|";
}

void DrawGraphLine(short fluctuation)
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

// If used more create overloads/templates
float RandomRange(int lowest, int highest)
{
    int range = (highest - lowest) + 1;
    return (rand() % range) + lowest; // Problematic if lowest is >0. 
}

int amount = 0;

float WeightedRNG(int Lo, int Hi, int weight)
{
    std::vector<int> rngResults;
    rngResults.reserve(5);

    if (weight > 0)
    {
        // Randomise 0 to Hi. Weight amount of times.
        for (int i = weight; i > 0; i--)
        {
            int hiResult = RandomRange(0, Hi);
            rngResults.push_back(hiResult);
        }

        // Include Lo result
        int loResult = RandomRange(Lo, 0);
        rngResults.push_back(loResult);
    }
    else if (weight < 0)
    {
        // Randomise Lo to 0. Weight amount of times.
        for (int i = weight; i < 0; i++)
        {
            int loResult = RandomRange(Lo, 0);
            rngResults.push_back(loResult);
        }

        // Include Hi result.
        int hiResult = RandomRange(0, Hi);
        rngResults.push_back(hiResult);
    }
    else
    {
        return RandomRange(Lo, Hi);
    }

    int randIndex = rand() % (abs(weight) + 1);

    return rngResults[randIndex];
}

float RandomiseFluctuation(int &weight)
{
    // Limit price from going out of graph bounds.
    int lowest = (assetPrice <= 8) ? 0 : -2;
    int highest = (assetPrice >= (GRAPH_TOP * moneyMultiplier)) ? 0 : 2;

    float fluctuation = WeightedRNG(lowest, highest, weight);

    // THIS COULD DO WITH TIDYING UP.
    // Increasing stocks more likely to keep increasing and vice versa.
    if (fluctuation >= 2) weight++;
    else if (fluctuation <= -2) weight--;
    else if (weight > 0) weight--;
    else if (weight < 0) weight++;
    //else if (weight > 0 && fluctuation < 0) weight = 0;
    //else weight = 0;

    // If decimal and int fluctuation are randomised using the same float it makes the overall graph line too centred
    //The addition of decimals is important for immersion and player fantasy of actually being a broker.
    lowest = (fluctuation <= -2) ? 0 : -100;
    highest = (fluctuation >= 2) ? 0 : 100;

    float decimal = RandomRange(lowest, highest);

    // Combine both randomised numbers.
    fluctuation += (decimal / 100);

    return fluctuation;
}