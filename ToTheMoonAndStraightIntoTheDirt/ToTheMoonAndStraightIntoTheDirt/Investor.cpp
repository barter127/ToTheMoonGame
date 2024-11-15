#include "Investor.h"
#include "Market.h"

void Investor::Buy()
{
	investorMoney -= assetOwned * assetPrice;
	assetOwned += assetOwned / actionInDays;
}

void Investor::Sell()
{
	float profit = (assetOwned / actionInDays) * 25;

	money += profit;
	totalProfit += profit;
	assetOwned -= assetOwned / actionInDays;
}
