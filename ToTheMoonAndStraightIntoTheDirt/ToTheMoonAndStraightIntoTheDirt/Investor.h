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
    unsigned short actionInDays = 0;

    // Investor stats determine their investment strategy.
    const unsigned short knowledge = 0;
    const unsigned short gambler = 0;
    const unsigned short hopeful = 0;

    void Buy();
    void Sell();
};

