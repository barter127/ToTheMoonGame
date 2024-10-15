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

        // For Debugging. Might double as feedback though.
        std::cout << "Bought " << amountToBuy << " for " << cost << std::endl;
    }
    else
    {
        std::cout << "You're trying to buy too much" << std::endl;
    }
}

void Sell(unsigned int amountToSell)
{
    assetOwned -= amountToSell;
    float sellPrice = amountToSell * assetPrice; // Calc price of sale.
    money += sellPrice;

    // For Debugging. Might double as feedback though.
    std::cout << "Sold " << amountToSell << " for " << sellPrice << std::endl;
}

void Skip()
{

}

/* To add a command: 
        - Add an appropriate name to enum below
        - Add if in HashCommands checking for string and returning matching enum type
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
        std::cerr << "ERROR. Nothing Entered " << std::endl;
    }

    return userInput;
}

// code assumes every input has a space change this

bool InputToCommand(std::string userInput)
{
    std::string command = "";
    int inputAmount = 0;

    // Find space
    std::size_t spacePosition = userInput.find(" ");

    // if space found.
    if (spacePosition != std::string::npos)
    {
        std::cout << "Else!";
        // Assign start of string to space.
        command = userInput.substr(0, spacePosition);

        // Assign from space to end of string.
        std::string amountString = userInput.substr(spacePosition, userInput.back());
        inputAmount = std::stoi(amountString);
    }
    else
    {
        command = userInput;
    }

    // Convert to Enum, then execute corresponding command.6
    switch (HashCommands(command))
    {
        case buy:
            Buy(inputAmount);
            return true;
            break;
        case sell:
            Sell(inputAmount);
            return true;
            break;
        case error:
            std::cerr << "ERROR. Invalid Command" << std::endl;
            return false;
            break;
    }

    // Failsafe
    std::cout << "Heather you fucked up.";
    return false;
}

int main()
{
    // Do and while do exactly same thing. Just more readable this way.
    do
    {
        std::string userInput = "";
        userInput = ReadInput();
        InputToCommand(userInput);
    }
    // Loop till invalid input
    while (!InputToCommand(ReadInput()));

    std::cout << "Money: " << money << " Amount Owned: " << assetOwned << std::endl;
}