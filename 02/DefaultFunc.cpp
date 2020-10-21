#include <string>
#include <iostream>
#include "DefaultFunc.h"


std::string Start_default()
{
	std::string res = "Start parsing\r"; 
	return res;
}


std::string Finish_default()
{
	std::string res = "Finish parsing\r"; 
	return res;
}


std::string WordParser_default(std::string &str)
{
	std::string res = "Parsered word is " + str + "\r"; 
	return res;
}


std::string DigitParser_default(int digit)
{
	std::string res = "Parsered number is " + std::to_string(digit) + "\r";  
    return res;	
}
