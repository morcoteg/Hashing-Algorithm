#include "HashFunc.h"

using namespace std;

/**
 * pg. 195 Hash Function at top of page
 */
unsigned int HashA(const std::string& s)
{
	int hashVal = 0;

	for (char c : s)
	{
		hashVal += c;
	}
	return hashVal;
}

/**
 * Hash function at bottom of page 195
 */
unsigned int HashB(const std::string& s)
{
	unsigned int hashVal = 0;

	for (char ch : s)
	{
		hashVal = 37 * hashVal + ch;
	}
	return hashVal;
}



/**
 * From the helproom board
 */
unsigned int HashC(const std::string& s)
{
	unsigned int magicNum = 31;
	unsigned int result = 0;
	for (const char c : s)
	{
		result *= magicNum;
		result += (unsigned int)c;
	}
	return result;
}