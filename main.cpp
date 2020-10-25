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

		auto encoded = base64::encode(data);
		std::cout << "Encoded: " << encoded << std::endl;

		auto decoded = base64::decode(encoded);
		std::string s2(begin(decoded), end(decoded));

		std::cout << "Decoded: " << s2 << std::endl;
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}