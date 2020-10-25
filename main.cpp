#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "base64.h"

int main()
{
	try
	{
		std::cout << "=========================" << std::endl;
		std::cout << "BASE64" << std::endl;
		std::cout << "=========================" << std::endl;
		std::string input = "Hello";
		std::string encoded = base64::encode(input);
		std::cout << "Encoded: " << encoded << std::endl;

		std::string decoded = base64::decode(encoded);
		std::cout << "Decoded: " << decoded << std::endl;

		std::cout << std::endl << "=========================" << std::endl;
		std::cout << "VIGENERE" << std::endl;
		std::cout << "=========================" << std::endl;

		std::string input2 = "hello";
		


	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}