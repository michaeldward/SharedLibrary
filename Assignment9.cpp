//Assignment 9; Michael Ward
#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <dlfcn.h>

std::string showHelp() { //if incorrect command is entered
	return "--- Assign 1 Help ---\n\n-fib [n] Compute the fibonacci of [n]\n\n-e [n] Compute the value of 'e' using [n] iterations\n\n-pi [n] Compute Pi to [n] digits";
}

double userInput(char prompt[]) { //handles user input and determines calculation
	//load shared library
	void* handle = dlopen("./library.so", RTLD_LAZY);
	if (!handle)
	{
		std::cout << "Couldn't open the shared library, error: " << dlerror() << std::endl;
		exit(1);
	}
	int (*fibInput)(int) = (int(*)(int))dlsym(handle, "fibInput");
	if (dlerror() != NULL)
	{
		std::cout << "Couldn't find 'fibInput', error: " << dlerror() << std::endl;
		exit(1);
	}

	double (*eInput)(int) = (double(*)(int))dlsym(handle, "eInput");
	if (dlerror() != NULL)
	{
	  std::cout << "Couldn't find 'eInput', error: " << dlerror() << std::endl;
	  exit(1);
	}
	double (*piInput)(int) = (double(*)(int))dlsym(handle, "piInput");
	if (dlerror() != NULL)
	{
	  std::cout << "Couldn't find 'piInput', error: " << dlerror() << std::endl;
	  exit(1);
	}
	int number = 0;
	if (prompt[0] == 'f') { //checks if prompt is fib
		if (prompt[1] == 'i') {
			if (prompt[2] == 'b') {
				if (std::isdigit(prompt[4])) {
					double number = std::stoi(&prompt[4]);
					fibReturn = fibInput(number);
					if (fibReturn == -1) { //number out of bounds
						std::cout << "Please enter a number between 1 and 14.\n";
					}
					return fibReturn;
				}
			}
		}
	}
	else if (prompt[0] == 'e') { //checks if prompt is e
		if (std::isdigit(prompt[2])) {
			double number = std::stoi(&prompt[2]);
			double eReturn = eInput(number);
			if (eReturn == -1) { //number out of bounds
				std::cout << "Please enter a number between 1 and 14.\n";
			}
			return eReturn;
		}
	}
	else if (prompt[0] == 'p') { //checks if prompt is pi
		if (prompt[1] == 'i') {
			if (std::isdigit(prompt[3])) {
				number = std::stoi(&prompt[3]);
				piReturn = piInput(number);
				if (piReturn == -1) { //number out of bounds
					std::cout << "Please enter a number between 1 and 14.\n";
				}
				return piReturn;
			}	
		}
	}
	return -2; //if input is not correct
}

bool checkQuit(char prompt[]) {
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
	while (!done) {
		char prompt[256];
		std::cout << "[cmd:] ";
		std::cin.getline(prompt, 255);
		if(checkQuit(prompt)) {
			done = true;
		}
		else {
			double userReturn = userInput(prompt);
			if (userReturn == -2) { //bad command entered
				std::cout << showHelp() << std::endl;
			}
			else if (userReturn != -1) { //-1 if number out of bounds
				std::cout << userReturn << std::endl;
			}
		}
	}
}