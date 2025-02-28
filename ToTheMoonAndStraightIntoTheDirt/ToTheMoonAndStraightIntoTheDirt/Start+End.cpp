#include "Start+End.h"
#include <iostream>
#include <windows.h>

// ---------- Start

// Prints words in font of the title screen.
// Big Money-NW by Nathan Bloomfield
void PrintToTheMoon()
{
    std::cout << R"(
$$$$$$$$\              $$$$$$$$\ $$\                       $$\      $$\
\__$$  __|             \__$$  __|$$ |                      $$$\    $$$ |
   $$ | $$$$$$\           $$ |   $$$$$$$\   $$$$$$\        $$$$\  $$$$ | $$$$$$\   $$$$$$\  $$$$$$$\
   $$ |$$  __$$\          $$ |   $$  __$$\ $$  __$$\       $$\$$\$$ $$ |$$  __$$\ $$  __$$\ $$  __$$\
   $$ |$$ /  $$ |         $$ |   $$ |  $$ |$$$$$$$$ |      $$ \$$$  $$ |$$ /  $$ |$$ /  $$ |$$ |  $$ |
   $$ |$$ |  $$ |         $$ |   $$ |  $$ |$$   ____|      $$ |\$  /$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |
   $$ |\$$$$$$  |         $$ |   $$ |  $$ |\$$$$$$$\       $$ | \_/ $$ |\$$$$$$  |\$$$$$$  |$$ |  $$ |
   \__| \______/          \__|   \__|  \__| \_______|      \__|     \__| \______/  \______/ \__|  \__|

)" << "\n";
}

void PrintAnd()
{
    std::cout << R"(
                          $$\ 
                          $$ |
 $$$$$$\  $$$$$$$\   $$$$$$$ |
 \____$$\ $$  __$$\ $$  __$$ |
 $$$$$$$ |$$ |  $$ |$$ /  $$ |
$$  __$$ |$$ |  $$ |$$ |  $$ |
\$$$$$$$ |$$ |  $$ |\$$$$$$$ |
 \_______|\__|  \__| \_______|

)" << "\n";
}

void PrintStraightInto()
{
    std::cout << R"(
 $$$$$$\    $$\                        $$\           $$\        $$\           $$$$$$\            $$\
$$  __$$\   $$ |                       \__|          $$ |       $$ |          \_$$  _|           $$ |
$$ /  \__|$$$$$$\    $$$$$$\  $$$$$$\  $$\  $$$$$$\  $$$$$$$\ $$$$$$\           $$ |  $$$$$$$\ $$$$$$\    $$$$$$\
\$$$$$$\  \_$$  _|  $$  __$$\ \____$$\ $$ |$$  __$$\ $$  __$$\\_$$  _|          $$ |  $$  __$$\\_$$  _|  $$  __$$\
 \____$$\   $$ |    $$ |  \__|$$$$$$$ |$$ |$$ /  $$ |$$ |  $$ | $$ |            $$ |  $$ |  $$ | $$ |    $$ /  $$ |
$$\   $$ |  $$ |$$\ $$ |     $$  __$$ |$$ |$$ |  $$ |$$ |  $$ | $$ |$$\         $$ |  $$ |  $$ | $$ |$$\ $$ |  $$ |
\$$$$$$  |  \$$$$  |$$ |     \$$$$$$$ |$$ |\$$$$$$$ |$$ |  $$ | \$$$$  |      $$$$$$\ $$ |  $$ | \$$$$  |\$$$$$$  |
 \______/    \____/ \__|      \_______|\__| \____$$ |\__|  \__|  \____/       \______|\__|  \__|  \____/  \______/
					   $$\   $$ |
					   \$$$$$$  |
					   \______/

)" << "\n";
}

void PrintTheDirt()
{
    std::cout << R"(
 $$$$$$$$\$$\                       $$$$$$$\  $$\            $$\
\__$$  __|$$ |                      $$  __$$\ \__|           $$ |
   $$ |   $$$$$$$\   $$$$$$\        $$ |  $$ |$$\  $$$$$$\ $$$$$$\
   $$ |   $$  __$$\ $$  __$$\       $$ |  $$ |$$ |$$  __$$\\_$$  _|
   $$ |   $$ |  $$ |$$$$$$$$ |      $$ |  $$ |$$ |$$ |  \__| $$ |
   $$ |   $$ |  $$ |$$   ____|      $$ |  $$ |$$ |$$ |       $$ |$$\
   $$ |   $$ |  $$ |\$$$$$$$\        $$$$$$$ |$$ |$$ |       \$$$$  |
   \__|   \__|  \__| \_______|      \_______/ \__|\__|        \____/

)" << "\n";
}

// Print TO THE MOON AND STRAIGHT INTO THE DIRT while playing a jingle.
void DisplayTitle()
{
	PrintToTheMoon();
	Beep(3500, 300);
	Sleep(600);

	PrintAnd();
	Beep(3500, 200);
	Sleep(100);

	PrintStraightInto();
	Beep(2500, 200);
	Sleep(400);

	PrintTheDirt();
	Beep(2500, 200);

	Sleep(1000);
	system("cls");
}

// Stats to show at end of game.
double totalProfit = 0;
double highestProfitOneDay = 0;
int assetsSold = 0;

// ---------- End

// Update stats
inline void UpdateHighestProfit(float profToCompare)
{
	if (profToCompare > highestProfitOneDay)
	{
		highestProfitOneDay = profToCompare;
	}
}

inline void UpdateTotalProfitStat(float newProfit)
{
	totalProfit += newProfit;
}

inline void UpdateTotalAssetSold(int newAssetSold)
{
	assetsSold += newAssetSold;
}

// Could use more clarity but is more concise than 3 functions
void UpdateEndStats(float profit, int assetsSold)
{
	UpdateHighestProfit(profit);
	UpdateTotalProfitStat(profit);
	UpdateTotalAssetSold(assetsSold);
}

void PrintEndStats()
{
	std::cout << "Total profit: " << totalProfit << "\n"
		<< "Highest Profit in one transaction: " << highestProfitOneDay << "\n"
		<< "Total assets sold: " << assetsSold << "\n";
}

enum endGameMessage {
	ThatsAll,
	Bane,
	EntrepeneurCEO,
	SpaceCowboy,
	NextTime,
	VideoTape,
	PaydayToo,
	EndMessagelength // Assigning numerical values in enum makes this useless
};

void PrintEndGameMessage()
{
	int randInt = rand() % EndMessagelength;

	switch (randInt)
	{
	case(ThatsAll):
		std::cout << "That's all Folks!";
		break;
	case(Bane):
		std::cout << "Is that bane?! Holy shit run!!!";
		break;
	case(EntrepeneurCEO):
		std::cout << "Goodbye \"Entrepeneur CEO\"";
		break;
	case(SpaceCowboy):
		std::cout << "SEE YOU SPACE COWBOY...";
		break;
	case(NextTime):
		std::cout << "See ya next time.";
		break;
	case(VideoTape):
		std::cout << "I've gotta return some videotapes";
		break;
	case(PaydayToo):
		std::cout << "You see, I need my payday too.";
		break;
	}

	std::cout << "\n";
}
