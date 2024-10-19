#include <iostream>
#include <string>
#include <chrono>

double money = 100; // needs negative values for debt
int assetOwned = 0;
float assetPrice = 10;
int day = 1;

int lastPriceHeight = 12;
int lastFluctuation = 0;

const int ASSET_MAX_AMOUNT = 1'000'000; // A mil

// 480 bytes
short marketGraph[120][2];

void Buy(unsigned int amountToBuy)
{
    float cost = amountToBuy * assetPrice;

    // If valid amountToBuy
    if (money - cost >= 0 && amountToBuy > 0 && assetOwned + amountToBuy < ASSET_MAX_AMOUNT)
    {
        money -= cost;
        assetOwned += amountToBuy;

        // Output feedback.
        std::cout << "Bought " << amountToBuy << " for " << cost << std::endl;
    }
    // If fail return appropriate error.
    else if (money - cost < 0) std::cerr << "Err. Your pockets are empty buddy... not enough money" << std::endl;
    else if (amountToBuy <= 0) std::cerr << "Err. You have to buy at least 1 doughnut!" << std::endl;
    else if (assetOwned + amountToBuy < ASSET_MAX_AMOUNT) std::cerr << "Err. You're trying to own more doughnuts than are in circulation! The market can't supply that many!" << std::endl;
}

void Sell(int amountToSell)
{
    float sellPrice = 0;

    // If valid amount to buy.
    if ((assetOwned - amountToSell) >= 0 && amountToSell > 0)
    {
        assetOwned -= amountToSell;
        sellPrice = amountToSell * assetPrice; // Calc price of sale.
        money += sellPrice;

        // Output feedback.
        std::cout << "Sold " << amountToSell << " for " << sellPrice << std::endl;
    }
    else if ((assetOwned - amountToSell) < 0) std::cerr << "Err. You're trying to sell more than you own!" << std::endl;
    else std::cerr << "Err. You have to sell at least 1 doughnut" << std::endl;
}

void NextDay()
{
    day++;
}

/* To add a command: 
        - Add an appropriate name to enum below
        - Add if in HashCommands checking for string and return matching enum type
        */

enum ListOfCommands {buy, sell, skip, error};

ListOfCommands HashCommands(std::string const& inString)
{
    if (inString == "buy") return buy;
    else if (inString == "b") return buy;
    else if (inString == "sell") return sell;
    else if (inString == "s") return sell;
    else if (inString == "skip") return skip;
    else return error;
}

std::string ReadInput()
{
    std::string userInput;

    // Get input & check string isn't empty
    while (std::cout << "Input command: " && getline(std::cin, userInput) && userInput.empty())
    {
        std::cerr << "Err. Nothing Entered " << std::endl;
    }
    return userInput;
}

bool IsNumber(std::string amount)
{
    for (int i = 0; i < amount.length(); i++)
    {
        // Char found.
        if (!isdigit(amount[i])) return false;
    }

    return true;
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

        // Set amount just after space to end of string
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

void TestAssign()
{
    srand(time(NULL));

    for (int i = 0; i < 120; i++)
    {
        marketGraph[i][1] = (rand() % 3) -1;

        // Cache field for readability and slight performance boost.
        int currentFluctuation = marketGraph[i][1];

        if (lastFluctuation == -1 || lastFluctuation == 0 && currentFluctuation == -1)
        {
            marketGraph[i][0] = --lastPriceHeight;
        }
        else if (lastFluctuation == 1 && currentFluctuation == 0 || currentFluctuation == 1)
        {
            marketGraph[i][0] = lastPriceHeight++;
        }
        else
        {
            marketGraph[i][0] = lastPriceHeight;
        }

    }
}

void TestRead()
{
    auto old = std::chrono::steady_clock::now();
    for (int i = 25; i > 0; i--)
    {
        for (int j = 0; j < 120; j++)
        {
            if (i == marketGraph[j][0])
            {
                if (marketGraph[j][1] == 1) std::cout << "/";
                else if (marketGraph[j][1] == 0) std::cout << "_";
                else std::cout << "\\";
            }
            else std::cout << " ";
        }

        std::cout << "\n";
    }
    auto time = std::chrono::steady_clock::now() - old;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
}

int main()
{
    //TestAssign();
    //TestRead();

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
        userInput = ReadInput();
        InputToCommand(userInput);


        //system("cls");
    }

    std::cout << "Money: " << money << " Amount Owned: " << assetOwned << std::endl;
}

/*
$$$$$$$$\              $$$$$$$$\ $$\                       $$\      $$\                               
\__$$  __|             \__$$  __|$$ |                      $$$\    $$$ |                              
   $$ | $$$$$$\           $$ |   $$$$$$$\   $$$$$$\        $$$$\  $$$$ | $$$$$$\   $$$$$$\  $$$$$$$\  
   $$ |$$  __$$\          $$ |   $$  __$$\ $$  __$$\       $$\$$\$$ $$ |$$  __$$\ $$  __$$\ $$  __$$\ 
   $$ |$$ /  $$ |         $$ |   $$ |  $$ |$$$$$$$$ |      $$ \$$$  $$ |$$ /  $$ |$$ /  $$ |$$ |  $$ |
   $$ |$$ |  $$ |         $$ |   $$ |  $$ |$$   ____|      $$ |\$  /$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |
   $$ |\$$$$$$  |         $$ |   $$ |  $$ |\$$$$$$$\       $$ | \_/ $$ |\$$$$$$  |\$$$$$$  |$$ |  $$ |
   \__| \______/          \__|   \__|  \__| \_______|      \__|     \__| \______/  \______/ \__|  \__|
*/