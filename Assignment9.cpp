//Assignment 9; Michael Ward
#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <cmath>

int fibonacci(int num) { //calculates the specified fibonacci number
	if (num == 0) { //if number entered is 0
		return 0;
	}
	long num1 = 0, num2 = 1;
	for (int i = 0; i < num - 1; ++i) {
		int temp = num2;
		num2 += num1;
		num1 = temp;
	}
	return num2;
}

int factorial(int num) { //calculates the factorial of the number specified
	int result = num;
	for (int i = num - 1; i > 0; --i) {
		result *= i;
	}
	return result;
}

double findE(int num) { //finds e to the specified precision using the Taylor series
	double result = 1;
	for (int i = 1; i < num; ++i) { 
		result += 1.0 / factorial(i);
	}
	return result;
}

long double findPi(int num) { //computes pi to the specified precision using the Nilakantha series
	int denominator = 2;
	long double result = 3;
	for (int i = 0; i < 10000; ++i) {
		result += 4.0 / (denominator*(denominator + 1)*(denominator + 2));
		denominator += 2;
		result -= 4.0 / (denominator*(denominator + 1)*(denominator + 2));
		denominator += 2;
	}
	result = roundf(result * powf(10, num)) / powf(10, num);
	return result;
}

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

std::string userInput() { //handles user input and determines calculation
	char prompt[256];
	std::cin.getline(prompt, 256);
	if (prompt[0] == '-') {
		if (prompt[1] == 'f') { //checks if prompt is fib
			if (prompt[2] == 'i') {
				if (prompt[3] == 'b') {
					return fibInput(prompt);
				}
			}
		}
		else if (prompt[1] == 'e') { //checks if prompt is e
			return eInput(prompt);
		}
		else if (prompt[1] == 'p') { //checks if prompt is pi
			if (prompt[2] == 'i') {
				return piInput(prompt);
			}
		}
	}
	return showHelp(); //if input is not correct
}

int main() {
	void* handle = dlopen("./DemoLib.so", RTLD_LAZY);
	if (!handle)
	{
		std::cout << "Couldn't open the shared library, error: " << dlerror() << std::endl;
		exit(1);
	}
	while (true) {
		std::cout << userInput() << std::endl;
	}
}