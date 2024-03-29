#pragma once

#include <string>
#include <vector>

namespace base64 {
	const char ENCODE_LOOKUP[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	const char PAD_CHARACTER = '=';

	using byte = std::uint8_t;

	// Encode the input in base64
	std::string encode(std::string input_str) {
		std::vector<byte> input(begin(input_str), end(input_str));

		std::string encoded;
		encoded.reserve(((input.size() / 3) + (input.size() % 3 > 0)) * 4);

		std::uint32_t temp{};
		auto it = input.begin();

		for (std::size_t i = 0; i < input.size() / 3; ++i) {
			temp = (*it++) << 16;
			temp += (*it++) << 8;
			temp += (*it++);
			encoded.append(1, ENCODE_LOOKUP[(temp & 0x00FC0000) >> 18]);
			encoded.append(1, ENCODE_LOOKUP[(temp & 0x0003F000) >> 12]);
			encoded.append(1, ENCODE_LOOKUP[(temp & 0x00000FC0) >> 6]);
			encoded.append(1, ENCODE_LOOKUP[(temp & 0x0000003F)]);
		}

		switch (input.size() % 3) {
		case 1:
			temp = (*it++) << 16;
			encoded.append(1, ENCODE_LOOKUP[(temp & 0x00FC0000) >> 18]);
			encoded.append(1, ENCODE_LOOKUP[(temp & 0x0003F000) >> 12]);
			encoded.append(2, PAD_CHARACTER);
			break;
		case 2:
			temp = (*it++) << 16;
			temp += (*it++) << 8;
			encoded.append(1, ENCODE_LOOKUP[(temp & 0x00FC0000) >> 18]);
			encoded.append(1, ENCODE_LOOKUP[(temp & 0x0003F000) >> 12]);
			encoded.append(1, ENCODE_LOOKUP[(temp & 0x00000FC0) >> 6]);
			encoded.append(1, PAD_CHARACTER);
			break;
		}

		return encoded;
	}

	// Decode the input in base64
	std::string decode(std::string input)
	{
		if (input.length() % 4 && input.length())
			throw std::runtime_error("Invalid base64 length!");

		int padding = 0;
		if (input[input.length() - 1] == PAD_CHARACTER) padding++;
		if (input[input.length() - 2] == PAD_CHARACTER) padding++;

		std::vector<byte> decoded;
		decoded.reserve(((input.length() / 4) * 3) - padding);

		std::uint32_t temp{};
		auto it = input.begin();

		while (it < input.end()) {
			for (std::size_t i = 0; i < 4; ++i) {
				temp <<= 6;
				if (*it >= 0x41 && *it <= 0x5A) temp |= *it - 0x41;
				else if (*it >= 0x61 && *it <= 0x7A) temp |= *it - 0x47;
				else if (*it >= 0x30 && *it <= 0x39) temp |= *it + 0x04;
				else if (*it == 0x2B)                temp |= 0x3E;
				else if (*it == 0x2F)                temp |= 0x3F;
				else if (*it == PAD_CHARACTER) {
					switch (input.end() - it) {
					case 1:
						decoded.push_back((temp >> 16) & 0x000000FF);
						decoded.push_back((temp >> 8) & 0x000000FF);
						return std::string(begin(decoded), end(decoded));
					case 2:
						decoded.push_back((temp >> 10) & 0x000000FF);
						return std::string(begin(decoded), end(decoded));
					default:
						throw std::runtime_error("Invalid padding in base64!");
					}
				}
				else throw std::runtime_error("Invalid character in base64!");

				++it;
			}

			decoded.push_back((temp >> 16) & 0x000000FF);
			decoded.push_back((temp >> 8) & 0x000000FF);
			decoded.push_back((temp) & 0x000000FF);
		}

		return std::string(begin(decoded), end(decoded));
	}
}