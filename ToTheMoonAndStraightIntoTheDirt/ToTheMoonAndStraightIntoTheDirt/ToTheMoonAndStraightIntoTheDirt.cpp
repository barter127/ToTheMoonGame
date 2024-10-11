#include <iostream>

long int money = 100; // needs negative values for debt
unsigned int assetOwned = 0;
float assetPrice = 10;

const int ASSET_MAX_AMOUNT = 1000000; // A mil



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

int main()
{
    int amountToBuy = 0;

    std::cout << "Input amount to buy: ";
    std::cin >> amountToBuy;

    Buy(amountToBuy);

    std::cout << "Money: " << money << " Amount Owned: " << assetOwned << std::endl
        << "Input amount to sell: ";
               

    std::cin >> amountToBuy;

    Sell(amountToBuy);

    std::cout << "Money: " << money << " Amount Owned: " << assetOwned;
}