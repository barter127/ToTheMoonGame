#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "inputvalidation.h"

// Player statistics.
double money = 100; // needs negative values for debt
int assetOwned = 0;
float assetPrice = 25;
int day = 1;

// Graph drawing.
float lastPrice = 12;
int lastGraphChange = 0;
int lastGraphHeight = 0;
const int GRAPH_TOP = 50;
const int GRAPH_BOTTOM = 1;

std::string lastCommandOutput;

const int ASSET_MAX_AMOUNT = 1'000'000; // A mil

// 480 bytes
short marketGraph[116][2];

struct investor
{
    float money;
    int assetOwned;
    int knowledge = 0;
    int gambler = 0;
    int hopeful = 0;
};

// List of commands.
void Buy(unsigned int amountToBuy);
void Sell(int amountToSell);
void NextDay();

/* To add a command:
        - Add an appropriate name to enum ListOfCommands
        - Add if in HashCommands() checking for string and return matching enum type
        - If the command causes the graph to be redrawn save any console output using ostringstream and the lastCommandOutput var.
        */
enum ListOfCommands { buy, sell, skip, error };
ListOfCommands HashCommands(std::string const& inString)
{
    if (inString == "buy") return buy;
    else if (inString == "b") return buy;
    else if (inString == "sell") return sell;
    else if (inString == "s") return sell;
    else if (inString == "skip") return skip;
    else return error;
}

void InputToCommand(std::string userInput);

// Handle Price.
inline void IncreasePrice(int increase);
inline void DecreasePrice(int decrease);

// Handle graph.
void DrawGraph();
void UpdateMarket();
// Used only once.
void IntialiseGraph();

int main()
{
    system("Color 0A");

    IntialiseGraph();
    DrawGraph();

    while (true)
    {
        // This could all be written on 1 line but it's not pretty.
        std::string userInput = "";
        std::cout << "> Current price: " << assetPrice << std::endl << std::endl;
        std::cout << "- Input command: ";
        userInput = GetValidString();
        InputToCommand(userInput);

        UpdateMarket();

         //Clear and draw graph.

        system("cls");
        DrawGraph();

        std::cout << lastCommandOutput;
    }
}


// Commands.
void Buy(unsigned int amountToBuy)
{
    float cost = amountToBuy * assetPrice;

    // If invalid input print proper error msg.
    if (money - cost < 0) std::cerr << "Err. Your pockets are empty buddy... not enough money" << std::endl;
    else if (amountToBuy <= 0) std::cerr << "Err. You have to buy at least 1 doughnut!" << std::endl;
    else if (assetOwned + amountToBuy > ASSET_MAX_AMOUNT) std::cerr << "Err. You're trying to own more doughnuts than are in circulation! The market can't supply that many!" << std::endl;

    else // If Valid input (has enough money, is buying at least 1, and not attempting to buy more than avalible)
    {
        money -= cost;
        assetOwned += amountToBuy;

        // Output feedback and save output for when console clears.
        std::ostringstream buffer;
        buffer << "> Bought " << amountToBuy << " for " << cost << ". You now own " << assetOwned << "." << std::endl;
        lastCommandOutput = buffer.str();
    }
}

void Sell(int amountToSell)
{
    float sellPrice = 0;

    // If invalid print proper error msg.
    if ((assetOwned - amountToSell) < 0) std::cerr << "Err. You're trying to sell more than you own!" << std::endl;
    else if (amountToSell < 0) std::cerr << "Err. You have to sell at least 1 doughnut" << std::endl;

    else // If Valid input (selling an amount they own and selling at least 1)
    {
        assetOwned -= amountToSell;
        sellPrice = amountToSell * assetPrice; // Calc price of sale.
        money += sellPrice;

        // Output feedback and save output for when console clears.
        std::ostringstream buffer;
        buffer << "> Sold " << amountToSell << " for " << sellPrice << ". You now own " << assetOwned << "." << std::endl;
        lastCommandOutput = buffer.str();
    }
}

void NextDay()
{
    std::ostringstream buffer;
    buffer << "Day Skipped";
    lastCommandOutput = buffer.str();
}

void InputToCommand(std::string userInput)
{
    std::string command = "";
    int inputAmount = 0;

    // Accept any casing.
    userInput = ToLowerCase(userInput);

    // Find space
    std::size_t spacePosition = userInput.find(" ");

    // if space found.
    if (spacePosition != std::string::npos)
    {
        // Set command as start of string to just before space.
        command = userInput.substr(0, spacePosition);

        // Set amount just after space to end of string.
        std::string amountString = userInput.substr(spacePosition + 1, userInput.back());

        // check int is in string
        if (!amountString.empty() && IsNumber(amountString))
        {
            inputAmount = std::stoi(amountString);
        }
        else if (!IsNumber(amountString))
        {
            std::cerr << "Err. Number contains char" << std::endl;
            return;
        }
        else
        {
            std::cerr << "Err. Nothing Input" << std::endl;
            return;
        }
    }

    // Convert to Enum, then execute corresponding command.
    switch (HashCommands(command))
    {
    case buy:
        Buy(inputAmount);
        break;
    case sell:
        Sell(inputAmount);
        break;
    case skip:
        NextDay();
        break;
    case error:
        std::cerr << "Err. Invalid Command" << std::endl;
        break;
    }
}

// Price.
inline void IncreasePrice(int increase)
{
    assetPrice += increase;
}

inline void DecreasePrice(int decrease)
{
    assetPrice += decrease;
}

// Graph.
void DrawGraph()
{
    // Loop for height.
    for (int i = 25; i > 0; i--)
    {
        if ((i * 2) % 5 == 0)
        {
            // Display graph.
            std::cout << i * 2 << "-";
        }
        else std::cout << "   ";

        // Draw seperater. 
        std::cout << "|";

        // Loop for graph width.
        for (int j = 0; j < 116; j++)
        {
            // If there is a value at this position.
            if (i == marketGraph[j][0])
            {
                // Draw corresponding output.
                if (marketGraph[j][1] == 1) std::cout << "/";
                else if (marketGraph[j][1] == 0) std::cout << "_";
                else std::cout << "\\";
            }
            else std::cout << " ";
        }

        std::cout << "\n";
    }
}

void UpdateMarket()
{
    // Move all fields over by one.
    for (int i = 0; i < 115; i++) // Loop 1 less than length.
    {
        marketGraph[i][0] = marketGraph[i + 1][0];
        marketGraph[i][1] = marketGraph[i + 1][1];
    }

    // Limit price. Limiting from a game POV but text based really limits things.
    int lowest = (assetPrice <= GRAPH_BOTTOM + 2) ? 0 : -2; // +2 to prevent price hitting 0
    int highest = (assetPrice >= GRAPH_TOP) ? 0 : 2;

    int range = (highest - lowest) + 1;
    int fluctuation = (rand() % range) + lowest; // Problematic if lowest is >0.

    IncreasePrice(fluctuation);

    int graphHeight = assetPrice / 2;
    marketGraph[115][0] = graphHeight;


    int graphChange = graphHeight - lastGraphHeight;
    marketGraph[115][1] = graphChange;

    // Check to align graph lines.
    if ((lastGraphChange == -1 || lastGraphChange == 0) && graphChange == 1)
    {
        marketGraph[115][0] = graphHeight - 1;
    }
    else
    {
        marketGraph[115][0] = graphHeight;
    }

    lastGraphHeight = graphHeight;
}

void IntialiseGraph()
{
    // Set Seed.
    srand(time(NULL));

    for (int i = 0; i < 116; i++)
    {
        UpdateMarket();
    }
}