#pragma once

#include <iostream>

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