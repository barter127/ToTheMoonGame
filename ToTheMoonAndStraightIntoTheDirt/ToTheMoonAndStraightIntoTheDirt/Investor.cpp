#include "Investor.h"

extern float assetPrice;

void Investor::Buy()
{
	investorMoney -= assetOwned * assetPrice;
	assetOwned += assetOwned / actionInDays;

	actionInDays--;
}

void Investor::Sell()
{
	float profit = (assetOwned / actionInDays) * 25;

	investorMoney += profit;
	totalProfit += profit;
	assetOwned -= assetOwned / actionInDays;

	actionInDays--;
}
