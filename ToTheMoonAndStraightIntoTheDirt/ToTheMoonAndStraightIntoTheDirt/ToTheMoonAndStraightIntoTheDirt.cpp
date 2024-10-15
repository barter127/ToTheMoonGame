#include <iostream>
#include <string>

double money = 100; // needs negative values for debt
unsigned int assetOwned = 0;
float assetPrice = 10;

const int ASSET_MAX_AMOUNT = 1'000'000; // A mil



/* Can't buy negative amount
   Sanitise value before function called */
void Buy(unsigned int amountToBuy)
{
    float cost = amountToBuy * assetPrice;

    if (money - cost >= 0)
    {
        money -= cost;
        assetOwned = amountToBuy;
    }
    else
    {
        std::cout << "You're trying to buy too much" << std::endl;
    }
}

void Sell(unsigned int amountToSell)
{
    assetOwned -= amountToSell;
    money += amountToSell * assetPrice;
}

enum ListOfCommands {buy, sell};

ListOfCommands Hash(std::string const& inString)
{
    if (inString == "buy") return buy;
    if (inString == "sell") return sell;
}

void ReadInput()
{
    std::string userInput;
    std::string command;
    int inputAmount = 0;

    std::cout << "Input command: ";
    getline(std::cin, userInput);

    // Find space
    std::size_t spacePosition = userInput.find(" ");

    // Assign start of string to space.
    command = userInput.substr(0, spacePosition);

    // Assign from space to end of string.
    std::string amountString = userInput.substr(spacePosition, userInput.back());
    inputAmount = std::stoi(amountString);

    switch (Hash(command))
    {
        case buy:
            Buy(inputAmount);
            break;
        case sell:
            Sell(inputAmount);
            break;
    }
        

    //if (command == "buy")
    //{
    //    Buy(amountToBuy);
    //}
}

int main()
{
    ReadInput();

    std::cout << "Money: " << money << " Amount Owned: " << assetOwned << std::endl
        << "Input amount to sell: ";

    std::cout << "Money: " << money << " Amount Owned: " << assetOwned;
}