//
// Made by Val (GH: theval-s), 2024
//
#include "crypto_lab1.h"


int main()
{
	while (true) {
		std::cout << "Crypto Lab 1. Choose one of the following:\n"
			"1. Monoalphabetic substitution cipher\n"
			"2. Caesar cipher\n"
			"3. Vigenere cipher\n"
			"4. Enigma\n"
			"5. Exit\n>";

		char opt;
		std::string input, mod;
		std::cin >> opt;
		std::array<int, 3> values = { 0,0,0 };
		switch (opt) {
		case '1':
			std::cout << "1. Encrypt\n2. Decrypt\n";
			std::cin >> values[0];
			if (values[0] == 1) {
				std::cout << "Please enter your input text (english only, no spaces)\n>";
				std::cin >> input;
				std::cout << monoalphabetic_sub_encrypt(input) << std::endl;
			}
			else if (values[0] == 2) {
				std::cout << "Please enter your input text (english only, no spaces)\n>";
				std::cin >> input;
				std::cout << monoalphabetic_sub_decrypt(input) << std::endl;
			}
			else std::cout << "Invalid option.\n";
			break;
		case '2':
			std::cout << "Please enter your input text (english only, no spaces) :\n>";
			std::cin >> input;
			std::cout << "Please enter the shift value, like '+3'/'3' for right shift, or '-3' for left shift:\n>";
			std::cin >> mod;
			try {
				values[0] = std::stoi(mod);
			}
			catch (const std::exception& e) {
				std::cout << "Conversion to int failed. Reason: " << e.what() << "\n";
				break;
			}
			std::cout << caesar_encrypt(input, values[0]) << std::endl;
			break;
		case '3':
			std::cout << "1. Encrypt\n2. Decrypt\n";
			std::cin >> values[0];
			if (values[0] == 1) {
				std::cout << "Please enter your input text (english only, no spaces)\n>";
				std::cin >> input;
				std::cout << "Please enter your key text (english only, no spaces)\n>";
				std::cin >> mod;
				std::cout << vigenere_encrypt(input, mod) << std::endl;
			}
			else if (values[0] == 2) {
				std::cout << "Please enter your input text (english only, no spaces)\n>";
				std::cin >> input;
				std::cout << "Please enter your key text (english only, no spaces)\n>";
				std::cin >> mod;
				std::cout << vigenere_decrypt(input, mod) << std::endl;
			}
			else std::cout << "Invalid option.\n";
			break;
		case '4':
			std::cout << "Please enter your input text (english only, no spaces) :\n>";
			std::cin >> input;

			//Handling rotor configuration
			std::cout << "Please enter rotors (1 to 8) that you want to use, as a number.\n"
				"For example, sequence of '123' will use rotor I as a left rotor, II as a middle, and III as a right rotor:\n>";
			std::cin >> mod;
			try {
				values[0] = std::stoi(mod);
				if (values[0] < 100 || values[0] > 888) throw std::invalid_argument("invalid format or invalid rotor number");
			}
			catch (const std::exception& e) {
				std::cout << "Conversion to int failed. Reason: " << e.what() << "\n";
				break;
			}
			values[2] = values[0] % 10;
			values[1] = (values[0] / 10) % 10;
			values[0] /= 100;

			std::cout << "Please enter the rotor positions and reflector (A, B or C) like this - 'AAAB' for rotor pos. AAA and reflector B:\n>";
			std::cin >> mod;
			std::cout << enigma_encrypt(input, values[0], values[1], values[2], mod) << std::endl;
			break;
		case '5':
			return 0;
		default:
			std::cout << "Invalid option.\n";
			break;
		}
#ifdef WIN32
		system("pause");
		system("cls");
#elif defined(__linux__) || defined(__unix__)
		system("read");
		system("clear");
#endif
	}
}
std::string monoalphabetic_sub_encrypt(const std::string &data) {
	static constexpr std::string_view ciphertext = "QWERTYUIOPLKJHGFDSAZXCVBNM";

	std::string ans;
	ans.reserve(data.size());
	for (char c : data) {
		if (!std::isalpha(c)) return ("Error: invalid character");
		ans.push_back(ciphertext[std::toupper(c) - 65]);
	}
	return ans;
}
std::string monoalphabetic_sub_decrypt(const std::string &input) {
	static constexpr std::string_view key = "QWERTYUIOPLKJHGFDSAZXCVBNM";
	std::string ans;
	ans.reserve(input.size());
	for (char c : input) {
		if (!std::isalpha(c)) return ("Error: invalid character");
		ans.push_back(static_cast<char>(key.find(std::toupper(c),0)+65));
	}
	return ans;
}


std::string caesar_encrypt(const std::string &data,const int &shift) {
	std::string ans;
	ans.reserve(data.size());
	for (char c : data) {

		if (c >= 'A' && c <= 'Z') {
			if (shift > 0 && c + shift > 'Z') c -= 26;
			//this can be changed to %26 but I'm going to leave it like that'
			//probably because i like how it filters characters
			else if (shift < 0 && c + shift < 'A') c += 26;
			ans.push_back(c + shift);
		}
		else if (c >= 'a' && c <= 'z') {
			if (shift > 0 && c + shift > 'z') c -= 26;
			else if (shift < 0 && c + shift < 'a') c += 26;
			ans.push_back(c + shift);
		}
		else {
			return ("Error: invalid character");
		}
	}
	return ans;
}

std::string vigenere_encrypt(const std::string &data, const std::string &key) {
	std::string ans;
	ans.reserve(data.size());
	int cur_index = 0;
	for (char c : data) {
		int shift = std::toupper(key[cur_index]) - 'A';

		if (c >= 'A' && c <= 'Z') {
			if (c + shift > 'Z') c -= 26;
			ans.push_back(c + shift);
		}
		else if (c >= 'a' && c <= 'z') {
			if (c + shift > 'z') c -= 26;
			ans.push_back(c + shift);
		}
		else {
			return ("Error: invalid character");
		}

		(cur_index == key.size() - 1) ? cur_index = 0 : cur_index++;
	}

	return ans;
}
std::string vigenere_decrypt(const std::string &data, const std::string &key) {
	std::string ans;
	ans.reserve(data.size());
	int cur_index = 0;
	for (char c : data) {
		if (!std::isalpha(c)) return ("Error: invalid character");
		int shift = std::toupper(key[cur_index]) - 'A';
		//h = -7
		//T
		//19-7
		ans.push_back((std::toupper(c) - shift - 'A' + 26) % 26 + 'A');
		(cur_index == key.size() - 1) ? cur_index = 0 : cur_index++;
	}
	return ans;
}

static constexpr std::array<std::pair<std::string_view, int>, 8> rotors = {{
	{"EKMFLGDQVZNTOWYHXUSPAIBRCJ", 17},
	{"AJDKSIRUXBLHWTMCQGZNPYFVOE", 5},
	{"BDFHJLCPRTXVZNYEIWGAKMUSQO", 22},
	{"ESOVPZJAYQUIRHXLNFTGKDCMWB", 10},
	{"VZBRGITYUPSDNHLXAWMJQOFECK", 25},
	{"JPGVOUMFYQBENHZRDKASXLICTW", 13},
	{"NZJHGRCXMYSWBOUFAIVLPEKQDT", 13},
	{"FKQHTLXOCBJSPDZRAMEWNIUYGV", 13}
}};
//the list of arguments can probably be shortened with array or struct
std::string enigma_encrypt(const std::string &data, const int &rotl_num, const int &rotm_num, const int &rotr_num, const std::string &rotor_settings) {

	if (rotl_num <= 0 || rotl_num > 8
		|| rotm_num <= 0 || rotm_num > 8
		|| rotr_num <= 0 || rotr_num > 8) return "Invalid rotors (negative or bigger than 8)";

	std::string_view rotor1 = rotors[rotr_num - 1].first,//right rotor
		rotor2 = rotors[rotm_num - 1].first, //middle rotor
		rotor3 = rotors[rotl_num - 1].first; //left rotor

	int rot1_index = 0, rot2_index = 0, rot3_index = 0;

	if (rotor_settings.size() != 4) return "Rotor positions and reflector format incorrect";
	else {
		if (std::isalpha(rotor_settings[0])) rot1_index = std::toupper(rotor_settings[0]) - 'A';
		if (std::isalpha(rotor_settings[1])) rot2_index = std::toupper(rotor_settings[1]) - 'A';
		if (std::isalpha(rotor_settings[2])) rot3_index = std::toupper(rotor_settings[2]) - 'A';
	}
	std::string reflector;
	if (rotor_settings[3] == 'A') reflector = "EJMZALYXVBWFCRQUONTSPIKHGD";
	else if (rotor_settings[3] == 'B') reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
	else if (rotor_settings[3] == 'C') reflector = "FVPJIAOYEDRZXWGCTKUQSBNMHL";
	else return "Invalid reflector";

	std::string ans;
	ans.reserve(data.size());
	for (char c : data) {
		if (!std::isalpha(c)) return ("Error: invalid character");

		(rot1_index == 25) ? rot1_index = 0 : rot1_index++;
		if (rot1_index == rotors[rotr_num - 1].second || (rotl_num > 5 && rot1_index == 25)) {
			(rot2_index == 25) ? rot2_index = 0 : rot2_index++;
		}


		char encrypted = rotor1[(std::toupper(c) - 'A' + rot1_index + 26) % 26];
		encrypted = rotor2[(encrypted - 'A' + rot2_index - rot1_index + 26) % 26];
		encrypted = rotor3[(encrypted - 'A' + rot3_index - rot2_index + 26) % 26];
		encrypted = reflector[(encrypted - 'A' - rot3_index + 26) % 26];

		encrypted = (rotor3.find((encrypted - 'A' + rot3_index + 26) % 26 + 'A') - rot3_index + 26) % 26 + 'A';
		encrypted = (rotor2.find((encrypted - 'A' + rot2_index + 26) % 26 + 'A') - rot2_index + 26) % 26 + 'A';
		encrypted = (rotor1.find((encrypted - 'A' + rot1_index + 26) % 26 + 'A') - rot1_index + 26) % 26 + 'A';

		ans.push_back(encrypted);

		if (rot2_index == rotors[rotm_num - 1].second - 1 || (rotm_num > 5 && rot2_index == 25)) {
			(rot2_index == 25) ? rot2_index = 0 : rot2_index++; //double stepping anomaly
			(rot3_index == 25) ? rot3_index = 0 : rot3_index++;
		}
	}
	return ans;
}
