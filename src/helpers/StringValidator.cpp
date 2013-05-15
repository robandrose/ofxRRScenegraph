#include "StringValidator.h"


/**
 *  Validates an email-address roughly following RFC 822
 *  danggerscheen https://github.com/sjspring90/Email-Validation/blob/master/Validation.cpp
 */


#define MAX_EMAIL_SIZE 255 // Just a constant, do not need equals or semicolon
#define VALID_LOCALPART_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890._-"
#define VALID_SUBDOMAINPART_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.-"
#define MAX_LOCALNAME_SIZE 64



bool StringValidator::isEmailValid(const string& emailAddress)
{
	// 1. Check emailAddress size, use length operation
	if (emailAddress.length() > MAX_EMAIL_SIZE)
	{
		//cout << "Error Code 1" << endl;
		//cout << emailAddress << endl;
		return false;
	}
    
	// 2. Find '@' symbol
	int atPosition = emailAddress.find('@');
	if (atPosition == string::npos) // means @ character not found
	{
		//cout << "Error Code 2" << endl;
		//cout << emailAddress << endl;
		return false;
	}
    
	// 3. Extract localPart and domain
	string localPart, domain;
    
	localPart = emailAddress.substr(0, atPosition);
	domain = emailAddress.substr(atPosition + 1);
    
	// CHECK localPart
	// 4. Check localPart size
	if (localPart.length() > 64 || localPart.length() == 0)
	{
		//cout << "Error Code 4" << endl;
		//cout << emailAddress << endl;
		return false;
	}
    
	// 5. Check localPart for valid characters
	if (localPart.find_first_not_of(VALID_LOCALPART_CHARS) != string::npos)
	{
		//cout << "Error Code 5" << endl;
		//cout << emailAddress << endl;
		return false;
	}
    /*
	// 6. Check localPart for '.' and '-' rules
	if (DotDashRules(localPart) == false) // Better way to do this
	{
		cout << "Error Code 6" << endl;
		cout << emailAddress << endl;
		return false;
	}
     */
	// CHECK domain
	// 7. Check domain size
	if (domain.length() > 255 || domain.length() == 0)
	{
		//cout << "Error Code 7" << endl;
		//cout << emailAddress << endl;
		return false;
	}
    
	// 8. Find '.' starting from the end
	int lastDot = domain.rfind(".");
    
	// 9. Extract TLD
	string topLevelDomain;
	if (lastDot != string::npos)
		topLevelDomain = domain.substr(lastDot + 1);
	else
	{
		//cout << "Error Code 9" << endl;
		//cout << emailAddress << endl;
		return false;
	}
    
	// 10. Validate TLD
	if (topLevelDomain.length() == 0)
		return false;
    
    
    
    
	// 11. Extract subdomain
	string subDomain = domain.substr(0, lastDot);
    
	// 12. Check subdomain for valid characters
	if (subDomain.find_first_not_of(VALID_SUBDOMAINPART_CHARS) != string::npos)
	{
		//cout << "Error Code 12" << endl;
		//cout << emailAddress << " " << endl;
		return false;
	}
    /*
	// 13. Check subdomain for '.' and '-' rules
	if (DotDashRules(subDomain) == false) // better way to do this
	{
		cout << "Error Code 13" << endl;
		cout << emailAddress << endl;	
		return false;
	}
    */
	return true;
}

/*
// Check the address for violations of the dot and dash rule
bool StringValidator::DotDashRules(const string& emailAddress)
{
	// Locate locations of any violations
	int doubleDot = emailAddress.find("..");
	int doubleDash = emailAddress.find("--");
	int dotDash = emailAddress.find(".-");
	int dashDot = emailAddress.find("-.");
    
	// If any violations are found, the email is invalid
	if (doubleDot != string::npos || doubleDash != string::npos || dotDash != string::npos || dashDot != string::npos)
		return false;
    
	// Check if the address begins with a dash or a period, NOT WORKING
	char firstChar = emailAddress[0];
	if (firstChar == '.' || firstChar == '-')
		return false;
    
	//Check if the address ends with a dash or period
	int lastCharPos = emailAddress.length();
	lastCharPos--; // Subtracts one from the position to account for arrays starting at zero
	char lastChar = emailAddress[lastCharPos];
	if (lastChar == '.' || lastChar == '-')
		return false;
}*/