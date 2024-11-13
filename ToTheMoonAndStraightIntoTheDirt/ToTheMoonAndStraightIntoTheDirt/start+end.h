#pragma once
#include <windows.h>

// Title Screen.
void PrintToTheMoon()
{
	std::cout << "$$$$$$$$\\              $$$$$$$$\\ $$\\                       $$\\      $$\\" << std::endl
		<< "\\__$$  __|             \\__$$  __|$$ |                      $$$\\    $$$ |" << std::endl
		<< "   $$ | $$$$$$\\           $$ |   $$$$$$$\\   $$$$$$\\        $$$$\\  $$$$ | $$$$$$\\   $$$$$$\\  $$$$$$$\\" << std::endl
		<< "   $$ |$$  __$$\\          $$ |   $$  __$$\\ $$  __$$\\       $$\\$$\\$$ $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\" << std::endl
		<< "   $$ |$$ /  $$ |         $$ |   $$ |  $$ |$$$$$$$$ |      $$ \\$$$  $$ |$$ /  $$ |$$ /  $$ |$$ |  $$ |" << std::endl
		<< "   $$ |$$ |  $$ |         $$ |   $$ |  $$ |$$   ____|      $$ |\\$  /$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |" << std::endl
		<< "   $$ |\\$$$$$$  |         $$ |   $$ |  $$ |\\$$$$$$$\\       $$ | \\_/ $$ |\\$$$$$$  |\\$$$$$$  |$$ |  $$ |" << std::endl
		<< "   \\__| \\______/          \\__|   \\__|  \\__| \\_______|      \\__|     \\__| \\______/  \\______/ \\__|  \\__|" << std::endl << std::endl;
}

void PrintAnd()
{
	std::cout << "                          $$\\ " << std::endl
		      << "                          $$ |" << std::endl
			  << " $$$$$$\\  $$$$$$$\\   $$$$$$$ |" << std::endl
			  << " \\____$$\\ $$  __$$\\ $$  __$$ |" << std::endl
			  << " $$$$$$$ |$$ |  $$ |$$ /  $$ |" << std::endl
			  << "$$  __$$ |$$ |  $$ |$$ |  $$ |" << std::endl
			  << "\\$$$$$$$ |$$ |  $$ |\\$$$$$$$ |" << std::endl
			  << " \\_______|\\__|  \\__| \\_______|" << std::endl << std::endl;
}

void PrintStraightInto()
{
	std::cout << "  $$$$$$\\    $$\\                        $$\\           $$\\        $$\\           $$$$$$\\            $$\\" << std::endl
			  << "$$  __$$\\   $$ |                       \\__|          $$ |       $$ |          \\_$$  _|           $$ |" << std::endl
			  << "$$ /  \\__|$$$$$$\\    $$$$$$\\  $$$$$$\\  $$\\  $$$$$$\\  $$$$$$$\\ $$$$$$\\           $$ |  $$$$$$$\\ $$$$$$\\    $$$$$$\\" << std::endl
			  << "\\$$$$$$\\  \\_$$  _|  $$  __$$\\ \\____$$\\ $$ |$$  __$$\\ $$  __$$\\\\_$$  _|          $$ |  $$  __$$\\\\_$$  _|  $$  __$$\\" << std::endl
			  << " \\____$$\\   $$ |    $$ |  \\__|$$$$$$$ |$$ |$$ /  $$ |$$ |  $$ | $$ |            $$ |  $$ |  $$ | $$ |    $$ /  $$ |" << std::endl
			  << "$$\\   $$ |  $$ |$$\\ $$ |     $$  __$$ |$$ |$$ |  $$ |$$ |  $$ | $$ |$$\\         $$ |  $$ |  $$ | $$ |$$\\ $$ |  $$ |" << std::endl
			  << "\\$$$$$$  |  \\$$$$  |$$ |     \\$$$$$$$ |$$ |\\$$$$$$$ |$$ |  $$ | \\$$$$  |      $$$$$$\\ $$ |  $$ | \\$$$$  |\\$$$$$$  |" << std::endl
			  << " \\______/    \\____/ \\__|      \\_______|\\__| \\____$$ |\\__|  \\__|  \\____/       \\______|\\__|  \\__|  \\____/  \\______/" << std::endl
			  << "					   $$\\   $$ |" << std::endl
			  << "					   \\$$$$$$  |" << std::endl
			  << "					   \\______/" << std::endl << std::endl;
		
}

void PrintTheDirt()
{
	std::cout << "$$$$$$$$\\ $$\\                       $$$$$$$\\  $$\\           $$\\" << std::endl
			  << "\\__$$  __|$$ |                      $$  __$$\\ \\__|           $$ |" << std::endl
			  << "   $$ |   $$$$$$$\\   $$$$$$\\        $$ |  $$ |$$\\  $$$$$$\\ $$$$$$\\" << std::endl
			  << "   $$ |   $$  __$$\\ $$  __$$\\       $$ |  $$ |$$ |$$  __$$\\\\_$$  _|" << std::endl
			  << "   $$ |   $$ |  $$ |$$$$$$$$ |      $$ |  $$ |$$ |$$ |  \\__| $$ |" << std::endl
			  << "   $$ |   $$ |  $$ |$$   ____|      $$ |  $$ |$$ |$$ |       $$ |$$\\" << std::endl
			  << "   $$ |   $$ |  $$ |\\$$$$$$$\\        $$$$$$$ |$$ |$$ |       \\$$$$  |" <<std::endl
			  << "   \\__|   \\__|  \\__| \\_______|      \\_______/ \\__|\\__|        \\____/" << std::endl << std::endl;
}

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


	/*
	* Big Money-NW by Nathan Bloomfield
	*	$$$$$$$$\              $$$$$$$$\ $$\                       $$\      $$\
		\__$$  __|             \__$$  __|$$ |                      $$$\    $$$ |
		   $$ | $$$$$$\           $$ |   $$$$$$$\   $$$$$$\        $$$$\  $$$$ | $$$$$$\   $$$$$$\  $$$$$$$\
		   $$ |$$  __$$\          $$ |   $$  __$$\ $$  __$$\       $$\$$\$$ $$ |$$  __$$\ $$  __$$\ $$  __$$\
		   $$ |$$ /  $$ |         $$ |   $$ |  $$ |$$$$$$$$ |      $$ \$$$  $$ |$$ /  $$ |$$ /  $$ |$$ |  $$ |
		   $$ |$$ |  $$ |         $$ |   $$ |  $$ |$$   ____|      $$ |\$  /$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |
		   $$ |\$$$$$$  |         $$ |   $$ |  $$ |\$$$$$$$\       $$ | \_/ $$ |\$$$$$$  |\$$$$$$  |$$ |  $$ |
		   \__| \______/          \__|   \__|  \__| \_______|      \__|     \__| \______/  \______/ \__|  \__|

		*						      $$\
									  $$ |
			 $$$$$$\  $$$$$$$\   $$$$$$$ |
			 \____$$\ $$  __$$\ $$  __$$ |
			 $$$$$$$ |$$ |  $$ |$$ /  $$ |
			$$  __$$ |$$ |  $$ |$$ |  $$ |
			\$$$$$$$ |$$ |  $$ |\$$$$$$$ |
			 \_______|\__|  \__| \_______|

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

			$$$$$$$$\ $$\                       $$$$$$$\  $$\            $$\
			\__$$  __|$$ |                      $$  __$$\ \__|           $$ |
			   $$ |   $$$$$$$\   $$$$$$\        $$ |  $$ |$$\  $$$$$$\ $$$$$$\
			   $$ |   $$  __$$\ $$  __$$\       $$ |  $$ |$$ |$$  __$$\\_$$  _|
			   $$ |   $$ |  $$ |$$$$$$$$ |      $$ |  $$ |$$ |$$ |  \__| $$ |
			   $$ |   $$ |  $$ |$$   ____|      $$ |  $$ |$$ |$$ |       $$ |$$\
			   $$ |   $$ |  $$ |\$$$$$$$\       $$$$$$$  |$$ |$$ |       \$$$$  |
			   \__|   \__|  \__| \_______|      \_______/ \__|\__|        \____/
	*/
}


// Stats to show at end of game.
double totalProfit = 0;
double highestProfitOneDay = 0;
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

void PrintEndStats()
{
	std::cout << "Total profit: " << totalProfit << std::endl
		<< "Highest Profit in one transaction: " << highestProfitOneDay << std::endl
		<< "Total assets sold: " << assetsSold << std::endl;
}

enum endGameMessage {
	ThatsAll,
	Bane,
	EntrepeneurCEO,
	SpaceCowboy,
	NextTime,
	VideoTape,
	PaydayToo,
	EndMessagelength
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
		std::cout << "Is that fucking bane?! Holy shit run!!!";
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

	std::cout << std::endl << std::endl;
}
