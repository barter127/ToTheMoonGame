#include "Investor.h"
#include <iostream>

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

			investorMoney -= buyAmount * assetPrice;
			assetOwned += buyAmount;

			actionInDays--;
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
		assetPrice -= 0.01 * sellAmount;
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

	assetPrice += 0.01 * maxPurchase;
}

void Investor::SellMax()
{
	int profit = assetOwned * assetPrice;

	investorMoney += profit;
	totalProfit += profit;
	assetOwned -= assetOwned;

	assetPrice -= 0.01 * assetOwned;
}

bool Investor::AssetOwned()
{
	if (assetOwned > 0) return true;

	return false;
}
