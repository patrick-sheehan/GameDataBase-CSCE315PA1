/* 
	Patrick Sheehan
	CSCE 315 - PA1
	27 January 2013
*/
#include "ResourceFunctions.h"

int ResourceFunctions::stringToInt(string s)
{
	return atoi(s.c_str());
}
string ResourceFunctions::intToString(int n)
{
	string s;
	ostringstream os;
	os << n;
	s = os.str();
	return s;
}
string ResourceFunctions::toLower(string s)
{
	for (int i = 0; s[i] != '\0'; i++)
		s[i] = tolower(s[i]);

	return (string)s;
}