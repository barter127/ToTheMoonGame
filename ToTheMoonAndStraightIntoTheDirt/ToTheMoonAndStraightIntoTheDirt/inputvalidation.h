#pragma once
#include <string>

// Checks each character in input string. Returns false if ANY non-digit is found.
bool IsNumber(std::string amount)
{
    for (int i = 0; i < amount.length(); i++)
    {
        // Char found.
        if (!isdigit(amount[i])) return false;
    }

    return true;
}

// Converts input to lowercase.
std::string ToLowerCase(std::string inputString)
{
    for (std::size_t i = 0, length = inputString.length(); i < length; i++)
    {
        inputString[i] = tolower(inputString[i]);
    }

    return inputString;
}