#pragma once
class Investor
{
private:
    float investorMoney = 0;
    unsigned int assetOwned = 0;
    float totalProfit = 0;

public:
    float assetBoughtPrice = 0; // Cumulative price their assets were bought at.
    bool isBuying = false;
    unsigned short actionInDays = 0; // Trade over these days.
    unsigned amountToTrade = 0; // Desired amount to buy or sell.

    // Investor stats determine their investment strategy.
    const unsigned short knowledge = 0; // Ability or inability to predict market trends.
    const unsigned short gambler = 0; // likelihood at selling at low profits higher the higher profit margin needs to be
    const unsigned short hopeful = 0; // Buy amount multiplier higher it is more they buy.

    void Buy();
    void Sell();
    void SellMax();
    void BuyMax();
    bool AssetOwned();
};

