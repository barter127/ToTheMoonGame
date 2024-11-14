#include <chrono>
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <map>
#include <functional>
#include "inputvalidation.h"
#include "start+end.h"

using namespace std::chrono_literals;

// Player statistics.
double money = 1000; // Needs negative values for possib;e debt mechanic.
int assetOwned = 0;
float assetPrice = 25.0;
int day = 1;

// Graph drawing.
float lastPrice = 12;
int lastGraphChange = 0;
int lastGraphHeight = 12;
const int GRAPH_TOP = 50;
const int GRAPH_BOTTOM = 1;
const float Money_Multiplier = 2.0;

std::string lastCommandOutput;

const int ASSET_MAX_AMOUNT = 1'000'000; // A mil

bool endGame = false;
std::string commandInput = "";

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

bool marketTrendingUp;

// Command input.
void GetCommand();
std::string GetCommandWord(std::string input);
template<typename varType>
auto GetParameter(std::string commandLine, typename varType, int parmIndex);

// List of commands.
void Buy();
void Sell();
void NextDay();
void Help();
void Exit();

std::map<std::string, std::function<void()>> commands
{
    {"buy", Buy},
    {"b", Buy},
    {"sell", Sell},
    {"s", Sell},
    {"help", Help},
    {"exit", Exit}
};

// Handle Price.
inline void ChangeAssetPrice(int increase);

// Handle graph.
void DrawGraph();
void EraseGraph();
void DrawYAxisLabel(int graphHeight);
void UpdateMarket();
float RandomRange(int lowest, int highest);
void DrawMarketTrend(int fluctuation);
// Used only once.
void IntialiseGraph();

bool timer = true;

// Timer code by The Cherno. Pretyy sure 90% of this isn't nessecary.
void Timer()
{
    while (true)
    {
        std::this_thread::sleep_for(3s);

        system("cls");
        UpdateMarket();
        DrawGraph();

        std::cout << "> Current price: " << assetPrice << std::endl << std::endl;
        std::cout << lastCommandOutput;
    }
}

int main()
{
    // Set console colour. BG: Black Text: Green
    system("Color 0A");

    //PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE PLEASE DON'T FORGET TO UNCOMMENT THIS
    //DisplayTitle();

    IntialiseGraph();
    DrawGraph();
    std::cout << "> Current price: " << assetPrice << std::endl << std::endl;
   
    std::thread Countdown(Timer);

    while (true)
    {
        GetCommand();


        if (endGame)
        {
            break;
        }
    }

    std::cout << std::endl;

    PrintEndGameMessage();
}

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
            std::cerr << "[!] Err.Invalid Command" << std::endl;

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
auto GetParameter(std::string commandLine, typename varType, int parmIndex)
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
    if (money - cost < 0) std::cerr << "[!] Err. Your pockets are empty buddy... not enough money" << std::endl;
    else if (amountToBuy <= 0) std::cerr << "[!] Err. You have to buy at least 1 doughnut!" << std::endl;
    else if (assetOwned + amountToBuy > ASSET_MAX_AMOUNT) std::cerr << "[!] Err. You're trying to own more doughnuts than are in circulation! The market can't supply that many!" << std::endl;

    else // If Valid input (has enough money, is buying at least 1, and not attempting to buy more than avalible)
    {
        money -= cost;
        assetOwned += amountToBuy;

        // Output feedback and save output for when console clears.
        std::ostringstream buffer;
        buffer << "> Bought " << amountToBuy << " for " << cost << ". You now own " << assetOwned << "." << std::endl;
        lastCommandOutput = buffer.str();
    }

    std::ostringstream buffer;
    buffer << "> Bought " << amountToBuy << " for " << cost << ". You now own " << assetOwned << "." << std::endl;
}

void Sell()
{
    int amountToSell = GetParameter(commandInput, 0, 1);

    float sellPrice = 0;

    // If invalid print proper error msg.
    if ((assetOwned - amountToSell) < 0) std::cerr << "[!] Err. You're trying to sell more than you own!" << std::endl;
    else if (amountToSell < 0) std::cerr << "[!] Err.You have to sell at least 1 doughnut" << std::endl;

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
    system("cls");
    UpdateMarket();
    DrawGraph();

    std::cout << "> Current price: " << assetPrice << std::endl << std::endl;
    std::cout << lastCommandOutput;
}

void Help()
{
    std::cout << ">> buy <amount>: Buys amount of doughnuts" << std::endl
        << ">> sell <amount>: Sells amount of doughnuts" << std::endl
        << ">> skip: Skips day" << std::endl
        << ">> help: Dude you just used it you know what it does" << std::endl
        << ">> exit: exits game" << std::endl << std::endl;
}

// Exits game.
void Exit()
{
    endGame = true;
}

// Price.
inline void ChangeAssetPrice(int increase)
{
    assetPrice += increase;
}

// Graph.
void DrawGraph()
{
    printf("\033[%d;%dH", 1, 1);

    // Loop for height.
    for (int gHeight = 25; gHeight > 0 ; gHeight--)
    {
        // Draw left side of graph.
        DrawYAxisLabel(gHeight);

        // Loop for graph width.
        for (int gWidth = 0; gWidth < 116; gWidth++)
        {
            // If there is a value at this position.
            if (gHeight == marketGraph[gWidth][0])
            {
                // Draw corresponding output.
                DrawMarketTrend(marketGraph[gWidth][1]);
            }
            else std::cout << " ";
        }

        std::cout << "\n";
    }
}

void EraseGraph()
{
    printf("\033[%d;%dH", 1, 1);

    // +1 for current price line
    int graphHeight = (GRAPH_TOP / Money_Multiplier) + 1;

    for (int i = 0; i < graphHeight; i++)
    {
        printf("\x1b[2K");
        std::cout << std::endl;
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

void DrawMarketTrend(int fluctuation)
{
    if (fluctuation == 1) std::cout << "/";
    else if (fluctuation == 0) std::cout << "_";
    else std::cout << "\\";
    // Plan to use moe vertical price changes fell short
    // the lines become slightly unaligned and makes it look weird.
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
    int lowest = (assetPrice <= GRAPH_BOTTOM + 2) ? 0 : -2;
    int highest = (assetPrice >= GRAPH_TOP) ? 0 : 2;

    float fluctuation = RandomRange(lowest, highest);

    // If decimal and int fluctuation are randomised using the same float it makes the overall graph line too centred
    //The addition of decimals is important for immersion and player fantasy of actually being a broker.
    
    lowest = (fluctuation <= -2) ? 0 : -100;
    highest = (fluctuation >= 2) ? 0 : 100;

    float decimal = RandomRange(lowest, highest);

    fluctuation += (decimal / 100);

    assetPrice += fluctuation;

    int graphHeight = round(assetPrice / Money_Multiplier);
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

void InvestorDecision()
{

}

float RandomRange(int lowest, int highest)
{
    int range = (highest - lowest) + 1;
    return (rand() % range) + lowest; // Problematic if lowest is >0.
}