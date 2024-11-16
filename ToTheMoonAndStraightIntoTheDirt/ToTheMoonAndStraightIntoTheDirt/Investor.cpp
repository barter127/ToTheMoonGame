#include "Investor.h"

extern float assetPrice;

void Investor::Buy()
{
	int maxPurchase = investorMoney / assetPrice;

	if (maxPurchase > 0)
	{
		int buyAmount = (maxPurchase / amountToTrade) * actionInDays;

		investorMoney -= buyAmount * assetPrice;
		assetOwned += buyAmount;

		actionInDays--;
	}	
}

void Investor::Sell()
{
	int sellAmount = amountToTrade / actionInDays;
	float profit = sellAmount * assetPrice;

	investorMoney += profit;
	totalProfit += profit;
	assetOwned -= sellAmount;

	actionInDays--;
	assetPrice -= 0.01 * sellAmount;
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
