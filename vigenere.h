#pragma once

#include <string>

namespace vigenere {

	const std::string LOOKUP_TABLE = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";

	// Find the index of a character in the lookup table
	int findTableIndex(char c) {
		for (int i = 0; i < LOOKUP_TABLE.size(); i++) {
			if (LOOKUP_TABLE[i] == c)
				return i;
		}

		return -1;
	}

	// Returns true if a character is in the lookup table
	bool isInTable(char c) {
		for (int i = 0; i < LOOKUP_TABLE.size(); i++) {
			if (LOOKUP_TABLE[i] == c)
				return true;
		}

		return false;
	}

	// Extends the key to repeat itself for the length of the input
	std::string extendKey(std::string input, std::string key) {
		if (key.size() >= input.size())
			return key;

		std::string newKey(input.size(), '-');

		int i, j;
		for (i = 0, j = 0; i < input.size(); ++i, ++j) {
			if (j == key.size())
				j = 0;

			newKey[i] = key[j];
		}

		newKey[i] = '\0';
		return newKey;
	}

	// Encrypt the input using a key
	std::string encrypt(std::string input, std::string key) {
		std::string newKey = extendKey(input, key);
		std::string encrypted(input.size(), '-');

		int i;
		for (i = 0; i < input.size(); ++i) {
			if (isInTable(input[i]))
				encrypted[i] = LOOKUP_TABLE[((findTableIndex(input[i]) + findTableIndex(newKey[i])) % LOOKUP_TABLE.size())];
			else
				encrypted[i] = input[i];
		}

		encrypted[i] = '\0';
		return encrypted;
	}

	// Decrypt the input using a key
	std::string decrypt(std::string input, std::string key) {
		std::string newKey = extendKey(input, key);
		std::string decrypted(input.size(), '-');

		int i;
		for (i = 0; i < input.size(); ++i) {
			if (isInTable(input[i]))
				decrypted[i] = LOOKUP_TABLE[(findTableIndex(input[i]) - findTableIndex(newKey[i]) + LOOKUP_TABLE.size()) % LOOKUP_TABLE.size()];
			else
				decrypted[i] = input[i];
		}

		decrypted[i] = '\0';
		return decrypted;
	}

}