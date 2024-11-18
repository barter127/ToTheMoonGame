#include "Fail_Investor.h"
#include <iostream>

extern float assetPrice;
extern const int ASSER_MAX_AMOUNT;

void Investor::Buy()
{
	// Validate variables.
	if (actionInDays > 0 && amountToTrade > 0)
	{
		int maxPurchase = investorMoney / assetPrice;

		// Has money to buy assets.
		if (maxPurchase > 0)
		{
			int buyAmount = (maxPurchase / amountToTrade) * actionInDays;
			float cost = buyAmount * assetPrice;


			investorMoney -= cost;
			investorAssetOwned += buyAmount;
			amountToTrade -= buyAmount;

			actionInDays--;
			assetPrice += (0.005f * maxPurchase);

			totalProfit -= cost;
		}
	}
}

void Investor::Sell()
{
	// Validate variables.
	if (actionInDays > 0 && amountToTrade > 0)
	{
		int sellAmount = amountToTrade / actionInDays;
		float profit = sellAmount * assetPrice;

		investorMoney += profit;
		totalProfit += profit;

		investorAssetOwned -= sellAmount;
		amountToTrade -= sellAmount;

		actionInDays--;
		assetPrice -= (0.01f * sellAmount);

		totalProfit += profit;
	};
}

void Investor::BuyMax()
{
	int maxPurchase = investorMoney / assetPrice;
	int cost = maxPurchase * assetPrice;

	investorMoney -= cost;
	totalProfit += cost;
	investorAssetOwned += maxPurchase;

	assetPrice += (0.01f * maxPurchase);
}

void Investor::SellMax()
{
	int profit = investorAssetOwned * assetPrice;

	investorMoney += profit;
	totalProfit += profit;
	investorAssetOwned = 0;

	assetPrice -= 0.01f * investorAssetOwned;
}

int Investor::GetAssetOwned()
{
	return investorAssetOwned;
}

int Investor::GetMaxPurchase()
{
	return (investorMoney / assetPrice);
}

bool Investor::CanAfford(int price)
{
	if (price < investorMoney)
	{
		return true;
	}

	return false;
}

/* Simulate investor decisions by comparing investor stats
* is abitrary in some places but generally does simulate investor decisions enough to be immersive and add strategy
*
* I'm not fully happy with the implementation of the AI but time constraints make it hard to improve :(
* THIS TOOK FUCKING AGES!!!!!*/
//void InvestorDecision(Investor& investor)
//{
//    // Profit if sold now
//    float currentProfit = (assetPrice * investor.GetAssetOwned()) - investor.assetBoughtPrice;
//
//    // Likelihood of selling.
//    int sellWeight = 0;
//    int foresight = marketTrendForecast * ((float)investor.knowledge / 5);
//
//    // If decision is already made perform decision.
//    if (investor.actionInDays > 0)
//    {
//
//        if (investor.GetAssetOwned() > 0)
//        {
//            investor.Buy();
//            investorsBuying++;
//
//            return;
//        }
//
//        else
//        {
//            investor.Sell();
//            investorsSelling++;
//
//            return;
//        }
//
//        return;
//    }
//
//    // Buy at predicted market low.
//    if (!marketTrendingUp && foresight >= marketTrendForecast && investor.CanAfford(assetPrice))
//    {
//        investor.actionInDays = marketTrendForecast;
//        investor.amountToTrade = investor.GetMaxPurchase() - (rand() % investor.GetMaxPurchase());
//
//        investor.Buy();
//        investorsBuying++;
//    }
//
//
//    // Can only buy
//    if (investor.GetAssetOwned() <= 0) return;
//
//
//    // Predict market peak. Sell most at peak.
//    if (marketTrendingUp && foresight >= marketTrendForecast)
//    {
//        // If profit is high enough start selling.
//        float gamblerMultiplier = (float)investor.gambler / 5.0f;
//        if (currentProfit >= investor.assetBoughtPrice * gamblerMultiplier)
//        {
//            investor.actionInDays = marketTrendForecast;
//            investor.amountToTrade = investor.GetAssetOwned();
//
//            investor.Sell();
//            investorsSelling++;
//        }
//
//        // Otherwise it will be held.
//    }
//
//    // Investor cannot see the fall. Sell late
//    else if (!marketTrendingUp && foresight <= marketTrendForecast)
//    {
//        if (currentProfit > investor.assetBoughtPrice)
//        {
//            investor.actionInDays = marketTrendForecast;
//            investor.amountToTrade = investor.GetAssetOwned();
//
//            investor.Sell();
//            investorsSelling++;
//        }
//    }
//}
//
//static bool investorThread = true;
//void InvestorThread()
//{
//    // Could be concerning at a larger scale.
//    while (true)
//    {
//        if (investorThread)
//        {
//            // Reset vars
//            investorsBuying = 0;
//            investorsSelling = 0;
//
//
//            for (Investor& investor : investorArr)
//            {
//                InvestorDecision(investor);
//            }
//
//            UpdateForecast();
//
//            investorThread = false;
//        }
//    }
//}