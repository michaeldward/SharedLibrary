extern "C" int fibInput(int prompt) { //handles user input for fibonacci calculation
	int num = std::stoi(&prompt[5]);
	if (num < 15 && num >= 0) {
		return fibonacci(num);
	}
	return -1; //if user enters incorrect value
}

extern "C" double eInput(int prompt) { //handles user input for e calculation
		if (num > 0 && num < 31) {
			return std::to_string(findE(num));
		}
	}
	return errorE(); //if user enters incorrect value
}

extern "C" std::string piInput(char* prompt) { //handles user input for pi calculation
	if (isdigit(prompt[4])) {
		int num = std::stoi(&prompt[4]);
		if (num > 0 && num < 11) {
			return std::to_string(findPi(num));
		}
	}
	return errorPi(); //if user enters incorrect value
}