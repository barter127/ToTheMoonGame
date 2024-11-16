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


using namespace std::chrono_literals;

std::string lastCommandOutput;

const int ASSET_MAX_AMOUNT = 1'000'000; // A mil

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

bool endGame = false;
std::string commandInput = "";

// 480 bytes
short marketGraph[116][2];

bool marketTrendingUp;
int marketTrendForecast; // How long the market will continue to trend this way.

// Command input.
void GetCommand();
std::string GetCommandWord(std::string input);
template<typename varType>
varType GetParameter(std::string commandLine, typename varType, int parmIndex);

// List of commands.
void Buy();
void Sell();
void NextDay();
void Help();
void Dong();
void Share();
void Exit();

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
    timerOn = true;

    while (timerOn)
    {
        std::this_thread::sleep_for(3s);

        NextDay();
    }
}

int main()
{
    // Set console colour. BG: Black Text: Green
    system("Color 0A");

    //PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE DON'T FORGET TO UNCOMMENT THIS
    // DisplayTitle();

    IntialiseGraph(marketGraph);
    DrawGraph(marketGraph);
    std::cout << "> Current price: " << assetPrice << "\n";
    std::cout << "> Money: " << money << "\n" << "\n";
   
    std::thread Countdown(Timer);

    while (!endGame)
    {
        GetCommand();
        std::cout << lastCommandOutput << "\n";
    }

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

void NextDay()
{
    system("cls");
    UpdateMarket(marketGraph);
    DrawGraph(marketGraph);

    std::cout << "> Current price: " << assetPrice << "\n";
    std::cout << "> Money: " << money << "\n";
    std::cout << lastCommandOutput << "\n";
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

void InvestorDecision(Investor& investor)
{
    // Profit if sold now
    float currentProfit = assetPrice - investor.assetBoughtPrice;

    // Likelihood of selling.
    int sellWeight = 0;

    int foresight = marketTrendForecast * (investor.knowledge / 100);

    // maxPossiblePurchase * (buyweight / 10)

    if (investor.actionInDays > 0)
    {
        // If decision is already made buy based on buy weight. 
        if (investor.isBuying)
        {
            investor.Buy();
            return;
        }

        else
        {
            investor.Sell();
            return;
        }
    }


    // Buy slowly
    if (!marketTrendingUp && foresight >= marketTrendForecast)
    {
        Buy();
        // calculate amount to buy.
    }


    // Player doesn't have anything and can only buy. Selling consideration is pointless.
    if (!investor.AssetOwned()) return;


    /* If investor predicts market will start trending down
    * start start selling slowly and sell most at predicted peak (end of actionInDays)
    */
    if (marketTrendingUp && foresight >= marketTrendForecast)
    {
        // If profit is high enough start selling.
        float gamblerMultiplier = investor.gambler / 100;
        if (currentProfit >= investor.assetBoughtPrice * gamblerMultiplier)
        {
            investor.actionInDays = marketTrendForecast;
        }
        else
        {
            // hold.
        }

    }

    // Investor cannot see the fall to come and will sell late
    else if (!marketTrendingUp && foresight <= marketTrendForecast)
    {
        // Sell faster / all.

    }
}