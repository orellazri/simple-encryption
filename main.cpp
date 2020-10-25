#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "base64.h"

int main()
{
	try
	{
		std::string input = "Hello";
		std::vector<base64::byte> data(begin(input), end(input));

		std::string encoded = base64::encode(data);
		std::cout << "Encoded: " << encoded << std::endl;

		std::string decoded = base64::decode(encoded);
		std::cout << "Decoded: " << decoded << std::endl;
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}