extern "C" int fibInput(int prompt) { //handles user input for fibonacci calculation
	int num = std::stoi(&prompt[5]);
	if (num < 15 && num >= 0) {
		return fibonacci(num);
	}
	return -1; //if user enters incorrect value
}

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

extern "C" double eInput(int prompt) { //handles user input for e calculation
		if (num > 0 && num < 31) {
			return findE(num);
		}
	}
	return -1; //if user enters incorrect value
}

double findE(int num) { //finds e to the specified precision using the Taylor series
	double result = 1;
	for (int i = 1; i < num; ++i) { 
		result += 1.0 / factorial(i);
	}
	return result;
}

int factorial(int num) { //calculates the factorial of the number specified
	int result = num;
	for (int i = num - 1; i > 0; --i) {
		result *= i;
	}
	return result;
}

extern "C" double piInput(int prompt) { //handles user input for pi calculation
	if (num > 0 && num < 11) {
		return findPi(num);
	}
	return -1; //if user enters incorrect value
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