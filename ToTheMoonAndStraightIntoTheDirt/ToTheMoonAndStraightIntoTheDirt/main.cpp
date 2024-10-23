#include <iostream>
#include <string>
#include <sstream>
#include "inputvalidation.h"

// Player statistics.
double money = 100; // needs negative values for debt
int assetOwned = 0;
float assetPrice = 10;
int day = 1;

// Graph drawing.
int lastPriceHeight = 12;
int lastFluctuation = 0;
const int GRAPH_TOP = 25;
const int GRAPH_BOTTOM = 1;

std::string lastCommandOutput;

const int ASSET_MAX_AMOUNT = 1'000'000; // A mil

// 480 bytes
short marketGraph[120][2];

// List of commands.
void Buy(unsigned int amountToBuy);
void Sell(int amountToSell);
void NextDay();

/* To add a command:
        - Add an appropriate name to enum ListOfCommands
        - Add if in HashCommands checking for string and return matching enum type
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

// Handle graph.
void DrawGraph();
void UpdateGraph();
// Used only once.
void IntialiseGraph();


int main()
{
    IntialiseGraph();
    DrawGraph();

    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;           
    //std::cout << "  /" << std::endl;
    //std::cout << " /" << std::endl;
    //std::cout << "/" << std::endl << std::endl << std::endl;

    while (true)
    {
        // This could all be written on 1 line but it's not pretty.
        std::string userInput = "";
        std::cout << "Input command: ";
        userInput = GetValidString();
        InputToCommand(userInput);

        UpdateGraph();

         // Clear and draw graph.
        system("cls");
        DrawGraph();

        std::cout << lastCommandOutput << std::endl;
    }

    std::cout << "Money: " << money << " Amount Owned: " << assetOwned << std::endl;
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
        buffer << "Bought " << amountToBuy << " for " << cost << std::endl;
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
        buffer << "Sold " << amountToSell << " for " << sellPrice << std::endl;
        lastCommandOutput = buffer.str();
    }
}

void NextDay()
{
    day++;
}

void InputToCommand(std::string userInput)
{
    std::string command = userInput;
    int inputAmount = 0;

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
        NextDay();
        break;
    case sell:
        Sell(inputAmount);
        NextDay();
        break;
    case skip:
        NextDay();
        break;
    case error:
        std::cerr << "Err. Invalid Command" << std::endl;
        break;
    }
}



// Graph.
void DrawGraph()
{
    // Loop for height.
    for (int i = 25; i > 0; i--)
    {
        // Loop for width.
        for (int j = 0; j < sizeof marketGraph / sizeof marketGraph[0]; j++)
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

void UpdateGraph()
{
    // Move all fields over by one.
    int lengthOfArray = sizeof marketGraph / sizeof marketGraph[0];
    for (int i = 0; i < lengthOfArray - 1; i++) // Loop 1 less than length.
    {
        marketGraph[i][0] = marketGraph[i + 1][0];
        marketGraph[i][1] = marketGraph[i + 1][1];
    }

    // Randomise fluctuation and assign to array.
    int fluctuationRange = lastPriceHeight >= GRAPH_TOP ? 2 : 3;
    int fluctuation = (rand() % fluctuationRange) - 1;

    if (lastPriceHeight <= GRAPH_BOTTOM)
    {
        fluctuation = (rand() % 2);
    }

    marketGraph[lengthOfArray - 1][1] = fluctuation;

    // Cache field for readability and slight performance boost.
    int currentFluctuation = marketGraph[lengthOfArray - 1][1];

    if (lastFluctuation == -1 || lastFluctuation == 0 && currentFluctuation == -1)
    {
        marketGraph[lengthOfArray - 1][0] = --lastPriceHeight;
    }
    else if (lastFluctuation == 1 && currentFluctuation == 0 || currentFluctuation == 1)
    {
        marketGraph[lengthOfArray - 1][0] = lastPriceHeight++;
    }
    else
    {
        marketGraph[lengthOfArray - 1][0] = lastPriceHeight;
    }
}

void IntialiseGraph()
{
    // Set Seed.
    srand(time(NULL));

    for (int i = 0; i < sizeof marketGraph / sizeof marketGraph[0]; i++)
    {
        UpdateGraph();
    }
}