#pragma once
#include <cstdlib>

class Investor
{
private:
    float investorMoney = 0;
    unsigned int investorAssetOwned = 0;
    float totalProfit = 0;

public:

    // Randomise stats.
    Investor():
        investorMoney(rand() % 1000 + 1),
        knowledge(rand() % 10 + 1),
        gambler(rand() % 10 + 1),
        hopeful(rand() % 10 + 1),

        investorAssetOwned(10)
    {}

    // Set stats.
    Investor(float money, unsigned short know, unsigned short gamble, unsigned short hope):
        investorMoney(money),
        knowledge(know),
        gambler(gamble),
        hopeful(hope)
    {}



    float assetBoughtPrice = 0; // Cumulative price their assets were bought at.
    unsigned short actionInDays = 0; // Trade over these days.
    unsigned amountToTrade = 0; // REMOVE

    // Investor stats determine their investment strategy.
    const unsigned short knowledge = 0; // Ability or inability to predict market trends.
    const unsigned short gambler = 0; // likelihood at selling at low profits. higher the stat higher the profit margin needs to be
    const unsigned short hopeful = 0; // Buy amount multiplier higher it is more they buy.

    void Buy();
    void Sell();
    void SellMax();
    void BuyMax();

    int GetAssetOwned();
    int GetMaxPurchase();
    bool CanAfford(int price);
};

