#pragma once

#include <string>

// Checks each character in input string. Returns false if ANY non-digit is found.
bool IsNumber(std::string amount);

// Converts input to lowercase.
std::string ToLowerCase(std::string inputString);

// Loops until a non-empty string is input.
// Returns error message if string is empty.
std::string GetValidString();

// Prolly only used to find spaces but modularity!
int NthOccurence(std::string strToCheck, std::string lookingFor, int n);