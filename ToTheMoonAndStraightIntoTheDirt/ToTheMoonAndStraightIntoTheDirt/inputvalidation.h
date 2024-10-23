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

/*
Loops until a non-empty string is input.
Returns error message if string is empty.
*/
std::string GetValidString()
{
    std::string userInput;

    // Get input & check string isn't empty
    while (getline(std::cin, userInput) && userInput.empty())
    {
        std::cerr << "Err. Nothing Entered " << std::endl;
    }
    return userInput;
}