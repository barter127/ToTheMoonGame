// Stats to show at end of game.
double totalProfit = 0;
double highestProfitOneDay; = 0;
int assetsSold = 0;

void UpdateHighestProfitDay(double profToCompare)
{
	if (profToCompare > highestProfitOneDay)
	{
		highestProfitOneDay = profToCompare;
	}
}

inline void UpdateTotalProfitStat(double newProfit)
{
	totalProfit += newProfit;
}

inline void UpdateTotalAssetSold(int newAssetSold)
{
	assetsSold += newAssetSold;
}

