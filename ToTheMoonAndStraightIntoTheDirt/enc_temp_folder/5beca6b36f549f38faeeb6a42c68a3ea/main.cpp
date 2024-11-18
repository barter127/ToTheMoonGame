#include <chrono>
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <map>
#include <functional>

#include "inputvalidation.h"
#include "Start+End.h"
#include "Investor.h"
#include "Graph.h"

const int ASSET_MAX_AMOUNT = 1'000'000; // A mil

// 480 bytes
short marketGraph[116][2];

// Graph vars.
float lastPrice = 12;
int lastGraphChange = 0;
int lastGraphHeight = 12;
const int GRAPH_TOP = 25;
const int GRAPH_BOTTOM = 1;
const int Money_Multiplier = 2;

// Player statistics.
double money = 1000; // Needs negative values for possible debt mechanic.
unsigned int assetOwned = 0;
float assetPrice = 25.0;
unsigned int day = 1; // Maybe problematic for long play sessions.


void UpdateForecast();
bool marketTrendingUp = true;
int marketTrendForecast = 5; // How long the market will continue to trend this way.

int investorsBuying = 0;
int investorsSelling = 0;

// If size is increased move to stack.
Investor investorArr[100];

void InvestorDecision(Investor& investor);

void NextDay();
inline void SetSeed();

#pragma region Commands

// List of commands.
void Buy();
void Sell();
void Help();
void Dong();
void Share();
void Exit();

// Command input.
void GetCommand();
std::string GetCommandWord(std::string input);
template<typename varType>
varType GetParameter(std::string commandLine, typename varType, int parmIndex);

#pragma endregion

bool endGame = false;
std::string commandInput = "";
std::string lastCommandOutput;

std::map<std::string, std::function<void()>> commands
{
    {"buy", Buy},
    {"b", Buy},
    {"sell", Sell},
    {"s", Sell},
    {"help", Help},
    {"dong", Dong},
    {"share", Share},
    {"exit", Exit}
};

static bool timerOn = true; 
void Timer()
{
    using namespace std::chrono_literals;

    timerOn = true;

    while (timerOn)
    {
        std::this_thread::sleep_for(3s);

        NextDay();
    }
}

static bool investorThread = true;
void InvestorThread()
{
    // Could be concerning at a larger scale.
    while (true)
    {
        if (investorThread)
        {
            // Reset vars
            investorsBuying = 0;
            investorsSelling = 0;


            for (Investor& investor : investorArr)
            {
                InvestorDecision(investor);
            }

            UpdateForecast();

            investorThread = false;
        }
    }
}

int main()
{
    // Set console colour. BG: Black, Text: Green
    system("Color 0A");

    //PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE DON'T FORGET TO UNCOMMENT THIS
    // DisplayTitle();

    SetSeed();

    IntialiseGraph(marketGraph);
    DrawGraph(marketGraph);
    std::cout << "> Current price: " << assetPrice << "\n";
    std::cout << "> Money: " << money << "\n" << "\n";
   
    // Start Threads.
    std::thread Countdown(Timer);
    //std::thread MarketDecision(InvestorThread);


    // Game loop
    while (!endGame)
    {
        GetCommand();
        std::cout << lastCommandOutput << "\n";
    }

    // Game end
    Countdown.join();
    //MarketDecision.join();

    std::cout << "\n";
    PrintEndGameMessage();
}

// I could have a seperate file for command func and logic but because it's so intertwined with vars in main it makes more sense here while developing commands.

// Read command inputs.
#pragma region Overloaded Conversion Functions

// To Int.
int ConvertType(int type, std::string input)
{
    // check int is in string
    if (input.empty())
    {
        std::cerr << "[!] Err. Parameters are empty" << std::endl;
        return -1;
    }
    // Is a number.
    else if (!IsNumber(input))
    {
        std::cerr << "[!] Err. Parameters contains char" << std::endl;
        return -1;
    }
    else
    {
        return std::stoi(input);
    };
}

// To String.
std::string ConvertType(std::string type, std::string input)
{
    return input;
}

#pragma endregion

// List of commands
#pragma region Commands

void GetCommand()
{
    bool validCommand = false;

    while (!validCommand)
    {
        getline(std::cin, commandInput);
        std::string commandWord = GetCommandWord(commandInput);

        // Accept any casing.
        commandWord = ToLowerCase(commandWord);

        if (commands.find(commandWord) != commands.end())
        {
            commands[commandWord]();
            validCommand = true;
        }

        else
            std::cerr << "[!] Err.Invalid Command" << "\n";

        std::cin.clear();
    }
}

// Reads the command word.
std::string GetCommandWord(std::string input)
{
    std::string command = input;
    int inputAmount = 0;

    // Find space
    std::size_t spacePosition = input.find(" ");

    // if space found.
    if (spacePosition != std::string::npos)
    {
        // Set command as start of string to just before space.
        command = input.substr(0, spacePosition);
    }

    return command;
}

// Call inside command function to get data from user input.
template<typename varType>
varType GetParameter(std::string commandLine, typename varType, int parmIndex)
{
    std::string parm = " ";
    varType type{}; // Maybe this is awful who knows.

    // Get position of nth space.
    size_t nthSpace = NthOccurence(commandLine, " ", parmIndex);
    size_t nextSpace = NthOccurence(commandLine, " ", parmIndex + 1);

    if (nextSpace == std::string::npos)
        parm = commandLine.substr(nthSpace + 1);

    else
        parm = commandLine.substr(nthSpace + 1, nextSpace - nthSpace - 1);

    return ConvertType(type, parm);
}


// Commands.
void Buy()
{
    int amountToBuy = GetParameter(commandInput, 0, 1);

    float cost = amountToBuy * assetPrice;

    // If invalid input print proper error msg.
    if (money - cost < 0) std::cerr << "[!] Err. Your pockets are empty buddy... not enough money" << "\n";
    else if (amountToBuy <= 0) std::cerr << "[!] Err. You have to buy at least 1 doughnut!" << "\n";
    else if (assetOwned + amountToBuy > ASSET_MAX_AMOUNT) std::cerr << "[!] Err. You're trying to own more doughnuts than are in circulation! The market can't supply that many!" << "\n";

    else // If Valid input (has enough money, is buying at least 1, and not attempting to buy more than avalible)
    {
        money -= cost;
        assetOwned += amountToBuy;

        // Output feedback and save output for when console clears.
        std::ostringstream buffer;
        buffer << "> Bought " << amountToBuy << " for " << cost << ". You now own " << assetOwned << "." << "\n";
        lastCommandOutput = buffer.str();
    }

    std::ostringstream buffer;
    buffer << "> Bought " << amountToBuy << " for " << cost << ". You now own " << assetOwned << "." << "\n";
}

void Sell()
{
    int amountToSell = GetParameter(commandInput, 0, 1);

    float sellPrice = 0;

    // If invalid print proper error msg.
    if ((assetOwned - amountToSell) < 0) std::cerr << "[!] Err. You're trying to sell more than you own!" << "\n";
    else if (amountToSell < 0) std::cerr << "[!] Err.You have to sell at least 1 doughnut" << "\n";

    else // If Valid input (selling an amount they own and selling at least 1)
    {
        assetOwned -= amountToSell;
        sellPrice = amountToSell * assetPrice; // Calc price of sale.
        money += sellPrice;

        // Output feedback and save output for when console clears.
        std::ostringstream buffer;
        buffer << "> Sold " << amountToSell << " for " << sellPrice << ". You now own " << assetOwned << "." << "\n";
        lastCommandOutput = buffer.str();
    }
}

void Help()
{
    std::ostringstream buffer;
    buffer << "Command List:" << "\n"
        << "    >> buy <amount>: Buys amount of doughnuts" << "\n"
        << "    >> sell <amount>: Sells amount of doughnuts" << "\n"
        << "    >> help: Dude you just used it you know what it does" << "\n"
        << "    >> dong: Prints the amount of money you have in Vietnamese Dong" << "\n"
        << "    >> share: Prints your share percentage" << "\n"
        << "    >> exit: exits game" << "\n";
    lastCommandOutput = buffer.str();
}

void Dong()
{
    std::ostringstream buffer;
    buffer << "> You have " << money * 32174.30 << " Dong" << "\n";
    lastCommandOutput = buffer.str();
}

void Share()
{
    std::ostringstream buffer;
    buffer << "> You have " << ((float)assetOwned / (float)ASSET_MAX_AMOUNT) * 100 << "% of the market" << "\n";
    lastCommandOutput = buffer.str();
}

// Exits game.
void Exit()
{
    endGame = true;
}


#pragma endregion

void NextDay()
{
    system("cls");
    UpdateMarket(marketGraph);
    DrawGraph(marketGraph);

    investorThread = true;

    std::cout << "> Current price: " << assetPrice << "\n";
    std::cout << "> Money: " << money << "\n";
    std::cout << lastCommandOutput << "\n";
}

/* Simulate investor decisions by comparing investor stats
* is abitrary in some places but generally does simulate investor decisions enough to be immersive and add strategy
* 
* I'm not fully happy with the implementation of the AI but time constraints make it hard to improve :( 
* THIS TOOK FUCKING AGES!!!!!*/
void InvestorDecision(Investor& investor)
{
    // Profit if sold now
    float currentProfit = (assetPrice * investor.GetAssetOwned()) - investor.assetBoughtPrice;

    // Likelihood of selling.
    int sellWeight = 0;
    int foresight = marketTrendForecast * ((float)investor.knowledge / 5);

    // If decision is already made perform decision.
    if (investor.actionInDays > 0)
    {

        if (investor.GetAssetOwned() > 0)
        {
            investor.Buy();
            investorsBuying++;

            return;
        }

        else
        {
            investor.Sell();
            investorsSelling++;

            return;
        }

        return;
    }

    // Buy at predicted market low.
    if (!marketTrendingUp && foresight >= marketTrendForecast && investor.CanAfford(assetPrice))
    {
        investor.actionInDays = marketTrendForecast;
        investor.amountToTrade = investor.GetMaxPurchase() - (rand() % investor.GetMaxPurchase());

        investor.Buy();
        investorsBuying++;
    }


    // Can only buy
    if (investor.GetAssetOwned() <= 0) return;


    // Predict market peak. Sell most at peak.
    if (marketTrendingUp && foresight >= marketTrendForecast)
    {
        // If profit is high enough start selling.
        float gamblerMultiplier = (float) investor.gambler / 5.0f;
        if (currentProfit >= investor.assetBoughtPrice * gamblerMultiplier)
        {
            investor.actionInDays = marketTrendForecast;
            investor.amountToTrade = investor.GetAssetOwned();

            investor.Sell();
            investorsSelling++;
        }

        // Otherwise it will be held.
    }

    // Investor cannot see the fall. Sell late
    else if (!marketTrendingUp && foresight <= marketTrendForecast)
    {
        if (currentProfit > investor.assetBoughtPrice)
        {
            investor.actionInDays = marketTrendForecast;
            investor.amountToTrade = investor.GetAssetOwned();

            investor.Sell();
            investorsSelling++;
        }
    }
}

void UpdateForecast()
{
    marketTrendForecast = (investorsBuying - investorsSelling) / 10;

    if (marketTrendForecast <= 0)
    {
        marketTrendingUp = !marketTrendingUp;
        marketTrendForecast = abs(marketTrendForecast);
    }
    else marketTrendForecast--;
}

inline void SetSeed()
{
    srand(time(NULL));
}