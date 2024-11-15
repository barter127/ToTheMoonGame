#pragma once
class Investor
{
private:
    float investorMoney = 0;
    int assetOwned = 0;
    float totalProfit = 0;

public:
    const float assetBoughtPrice = 0; // Cumulative price their assets were bought at.
    bool isBuying = false;
    short actionInDays = 0;

    // Investor stats may change and determine their investment strategy.
    short knowledge = 0;
    short gambler = 0;
    short hopeful = 0;

    void Buy();
    void Sell();
};

