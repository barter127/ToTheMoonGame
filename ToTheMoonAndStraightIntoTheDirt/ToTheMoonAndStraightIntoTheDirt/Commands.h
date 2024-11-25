#pragma once
#include <string>
#include <map>
#include <functional>


// Player statistics.
extern double money;
extern unsigned int assetOwned;
extern float assetPrice;
extern unsigned int day;

extern bool endGame;
extern const int MAX_ASSET_AMOUNT;

extern std::string commandInput;
extern std::string lastCommandOutput;

extern std::map<std::string, std::function<void()>> commands;

// List of commands.
void Buy();
void Sell();
void Help();
void Dong();
void Share();
void Exit();

// Command input.
void GetCommand();
std::string GetCommandWord(std::string input);
template<typename varType>
varType GetParameter(std::string commandLine, typename varType, int parmIndex);


