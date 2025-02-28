#include "InputValidation.h"

#include <string>
#include <iostream>

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
        std::cerr << "[!]Err. Nothing Entered. Try again.\n";
    }
    return userInput;
}

// Find nth time lookingFor appears in string strToCheck.
// Mainly used for command system to find where parameters may be.
int NthOccurence(std::string strToCheck, std::string lookingFor, int n)
{
    size_t pos = 0;
    int iter = 0;

    while (iter != n)
    {
        pos++;
        pos = strToCheck.find(lookingFor, pos);

        //  nth not found return failcode.
        if (pos == std::string::npos)
            return -1;

        iter++;
    }

    return pos;
}