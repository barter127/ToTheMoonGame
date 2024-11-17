#include "Investor.h"
#include <iostream>

extern float assetPrice;
extern float assetPrice;

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
			assetOwned += buyAmount;

			actionInDays--;
			assetPrice += 0.01f;

			totalProfit -= cost;
		}
	}
	else std::cerr << "Tried to buy with invalid variables";
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
		assetOwned -= sellAmount;

		actionInDays--;
		assetPrice -= (0.01f * sellAmount);

		totalProfit += profit;
	}
	else std::cerr << "Tried to sell with invalid variables";
}

void Investor::BuyMax()
{
	int maxPurchase = investorMoney / assetPrice;
	int cost = maxPurchase * assetPrice;

	investorMoney -= cost;
	totalProfit += cost;
	assetOwned -= assetOwned;

	assetPrice += (0.01f * maxPurchase);
}

void Investor::SellMax()
{
	int profit = assetOwned * assetPrice;

	investorMoney += profit;
	totalProfit += profit;
	assetOwned -= assetOwned;

	assetPrice -= 0.01f * assetOwned;
}

int Investor::GetAssetOwned()
{
	return assetOwned;
}
