// Keypad.cpp
// Member-function definition for class Keypad (the ATM's keypad).
#include <iostream>
using namespace std;

#include "Keypad.h" // Keypad class definition

// return an integer value entered by user
int Keypad::getInput() const
{
	int input; // variable to store the input
	cin >> input; // we assume that user enters an integer
	return input; // return the value entered by user
} // end function getInput
