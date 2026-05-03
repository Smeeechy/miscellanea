#include <iostream>
#include <string>
#include <string_view>
#include <random>
#include <vector>
#include <algorithm>

struct Code {
	std::string_view name;
	std::string_view ansi_fg;
	int num;
};

const Code codes[] = {
	{"Black", "\033[38;5;16m", 0},
	{"Brown", "\033[38;5;94m", 1},
	{"Red", "\033[38;5;196m", 2},
	{"Orange", "\033[38;5;208m", 3},
	{"Yellow", "\033[38;5;226m", 4},
	{"Green", "\033[38;5;46m", 5},
	{"Blue", "\033[38;5;21m", 6},
	{"Purple", "\033[38;5;129m", 7},
	{"Gray", "\033[38;5;244m", 8},
	{"White", "\033[38;5;231m", 9}
};
std::string_view ansi_bg = "\033[48;5;180m\033[1m";
std::string_view ansi_reset = "\033[0m";

std::random_device device;
std::mt19937 gen(device());
std::uniform_int_distribution<> distr(0, 9);

bool test() {
	// create random resistor
	std::vector<int> code;
	int first = std::max(1, distr(gen));
	code.push_back(first);
	for (int i = 0; i < 3; i++) {
		code.push_back(distr(gen));
	}

	// build out actual resistance value
	std::string actual;
	for (int i = 0; i < 3; i++) {
		actual += std::to_string(codes[code[i]].num);
	}
	for (int i = 0; i < codes[code[3]].num; i++) {
		actual += "0";
	}

	// print out the prompt with resistor diagram
	std::cout << "what is the resistance of ";
	std::cout << "--";
	for (int n : code) {
		std::cout << ansi_bg << codes[n].ansi_fg << "|" << ansi_reset;
	}
	std::cout << "-- in ohms?" << std::endl;

	// store user input
	std::string input;
	std::cin >> input;

	// remove commas
	size_t commaIndex;
	while ((commaIndex = input.find(',')) != std::string::npos) {
		input.replace(commaIndex, 1, "");
	}

	// replace 'k' or 'K' with '000'
	size_t kIndex;
	if ((kIndex = input.find('k')) != std::string::npos || (kIndex = input.find('K')) != std::string::npos) {
		input.replace(kIndex, 1, 3, '0');
	}

	// replace 'm' or 'M' with '000000'
	size_t mIndex;
	if ((mIndex = input.find('m')) != std::string::npos || (mIndex = input.find('M')) != std::string::npos) {
		input.replace(mIndex, 1, 6, '0');
	}

	// replace 'g' or 'G' with '000000000'
	size_t gIndex;
	if ((gIndex = input.find('g')) != std::string::npos || (gIndex = input.find('G')) != std::string::npos) {
		input.replace(gIndex, 1, 9, '0');
	}

	// check normalized input against actual resistance
	if (input == actual) {
		std::cout << "Correct!" << std::endl << std::endl;
		return true;
	} else {
		std::cout << "The correct answer is " << actual << std::endl << std::endl;
		return false;
	}
}

int main() {
	int correct = 0;
	int length = 3;
	for (int i = 0; i < length; i++) {
		if (test()) {
			correct++;
		}
	}

	std::cout << "You got " << correct << "/" << length << " correct (" << 100.0 * (correct / (float) length) << "%)" << std::endl;

	return 0;
}
