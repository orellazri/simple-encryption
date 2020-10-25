#include <iostream>
#include <string>
#include <fstream>

#include "base64.h"
#include "vigenere.h"

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char** argv)
{
	if (argc != 4) {
		std::cout << "Usage: [e:encrypt|d:decrypt] [INPUT] [KEY]" << std::endl;
		std::cout << "Example: 0 \"This is a secret!\" DontTell" << std::endl;
		std::cout << "It is recommended that the key will not be longer than the input." << std::endl;
		return -1;
	}

	bool modeEncrypt = argv[1][0] == 'e';
	std::string input = argv[2];
	std::string key = argv[3];
	std::string result = "";

	try
	{
		// Encrypt
		if (modeEncrypt) {
			result = vigenere::encrypt(base64::encode(input), key);
		}
		// Decrypt
		else {
			result = base64::decode(vigenere::decrypt(input, key));
		}
	}
	catch (std::exception & e)
	{
		std::cerr << "Could not decrypt input with the given key." << std::endl;
		LOG(e.what());
	}

	if (result.compare("")) {
		if (modeEncrypt)
			std::cout << "Encrypted input: " << std::endl;
		else
			std::cout << "Decrypted input: " << std::endl;

		std::cout << result << std::endl;
	}

	return 0;
}