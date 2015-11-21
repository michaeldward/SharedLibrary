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

int userInput(char prompt[]) { //handles user input and determines calculation
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
				if (std::isdigit(prompt[5])) {
					number = std::stoi(&prompt[4]) * 10 + std::stoi(&prompt[5]);
				}
				else {
					number = std::stoi(&prompt[4]);
				}
				return fibInput(number);
			}
		}
	}
	else if (prompt[0] == 'e') { //checks if prompt is e
		if (std::isdigit(prompt[3])) {
			number = std::stoi(&prompt[2]) * 10 + std::stoi(&prompt[3]);
		}
		else {
			number = std::stoi(&prompt[2]);
		}
		return eInput(number);
	}
	else if (prompt[0] == 'p') { //checks if prompt is pi
		if (prompt[1] == 'i') {
			if (std::isdigit(prompt[4])) {
				number = std::stoi(&prompt[3]) * 10 + std::stoi(&prompt[4]);
			}
			else {
				number = std::stoi(&prompt[3]);
			}
			return piInput(number);
		}
	}
	return -1; //if input is not correct
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
		std::cin.getline(prompt, 256);
		if(checkQuit) {
			done = true;
			std::cout << "I WILL QUIT";
		}
		else {
			std::cout << userInput(prompt) << std::endl;
		}
	}
}