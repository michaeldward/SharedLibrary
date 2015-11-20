//Assignment 9; Michael Ward
#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <dlfcn.h>

std::string errorFib() { //if incorrect value is entered for fibonacci calculation
	return "Please enter a number between 0 and 14.";
}

std::string errorPi() { //if incorrect value is entered for pi calculation
	return "Please enter a number between 1 and 10.";
}

std::string errorE() { //if incorrect value is entered for e calculation
	return "Please enter a number between 1 and 30.";
}

std::string fibInput(char* prompt) { //handles user input for fibonacci calculation
	if (isblank(prompt[4])) {
		if (isdigit(prompt[5])) {
			int num = std::stoi(&prompt[5]);
			if (num < 15 && num >= 0) {
				return std::to_string(fibonacci(num));
			}
		}
	}
	return errorFib(); //if user enters incorrect value
}

std::string eInput(char* prompt) { //handles user input for e calculation
	if (isdigit(prompt[3])) {
		int num = std::stoi(&prompt[3]);
		if (num > 0 && num < 31) {
			return std::to_string(findE(num));
		}
	}
	return errorE(); //if user enters incorrect value
}

std::string piInput(char* prompt) { //handles user input for pi calculation
	if (isdigit(prompt[4])) {
		int num = std::stoi(&prompt[4]);
		if (num > 0 && num < 11) {
			return std::to_string(findPi(num));
		}
	}
	return errorPi(); //if user enters incorrect value
}

std::string showHelp() { //if incorrect command is entered
	return "--- Assign 1 Help ---\n\n-fib [n] Compute the fibonacci of [n]\n\n-e [n] Compute the value of 'e' using [n] iterations\n\n-pi [n] Compute Pi to [n] digits";
}

int userInput(char prompt[]) { //handles user input and determines calculation
	int number = 0;
	if (prompt[0] == 'f') { //checks if prompt is fib
		if (prompt[1] == 'i') {
			if (prompt[2] == 'b') {	
				if (std::isdigit(prompt[5])) {
					number = std::stoi(prompt[4]) * 10 + std::stoi(prompt[5]);
				}
				else {
					number = std::stoi(prompt[4]);
				}
				return fibInput(number);
			}
		}
	}
	else if (prompt[0] == 'e') { //checks if prompt is e
		if (std::isdigit(prompt[3])) {
			number = std::stoi(prompt[2]) * 10 + std::stoi(prompt[3]);
		}
		else {
			number = std::stoi(prompt[2]);
		}
		return eInput(number);
	}
	else if (prompt[0] == 'p') { //checks if prompt is pi
		if (prompt[1] == 'i') {
			if (std::isdigit(prompt[4])) {
				number = std::stoi(prompt[3]) * 10 + std::stoi(prompt[4]);
			}
			else {
				number = std::stoi(prompt[3]);
			}
			return piInput(number);
		}
	}
	return -1; //if input is not correct
}

bool checkQuit(prompt[]) {
	if(prompt[0] == 'q') {
		if (prompt[1] == 'u') {
			if (prompt[2] == 'i') {
				if (prompt[3] == 't') {
					return true; //user entered 'quit'
				}
			}
		}
	}
	return false; //user didn't enter 'quit'
}

int main() {
	bool done = false;
	void* handle = dlopen("./Library.so", RTLD_LAZY);
	if (!handle)
	{
		std::cout << "Couldn't open the shared library, error: " << dlerror() << std::endl;
		exit(1);
	}
	double (*fibInput)(int) = (double(*)(int))dlsym(handle, "fibInput");
	if (dlerror() != NULL)
	{
		std::cout << "Couldn't find 'fibInput', error: " << dlerror() << std::endl;
		exit(1);
	}

	double (*eInput)(int, double) = (double(*)(int, double))dlsym(handle, "eInput");
	if (dlerror() != NULL)
	{
	  std::cout << "Couldn't find 'eInput', error: " << dlerror() << std::endl;
	  exit(1);
	}
	double (*piInput)(int, double) = (double(*)(int, double))dlsym(handle, "piInput");
	if (dlerror() != NULL)
	{
	  std::cout << "Couldn't find 'piInput', error: " << dlerror() << std::endl;
	  exit(1);
	}
	while (!done) {
		char prompt[256];
		std::cout << "[cmd:] " << std::endl;
		std::cin.getline(prompt, 256);
		if(checkQuit) {
			done = true;
		}
		else {
			std::cout << userInput(prompt) << std::endl;
		}
	}
}