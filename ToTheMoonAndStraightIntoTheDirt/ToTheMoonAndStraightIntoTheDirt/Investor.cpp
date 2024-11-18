#include "Investor.h"
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