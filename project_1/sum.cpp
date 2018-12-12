/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Maryash
Assignment: Project1A

The program reads a sequence of ints and prints their sum.
*/


#include <iostream>
using namespace std;

int main() {
	int a;               //we'll read into here
	int b = 0;           //running total
	while (cin >> a) {
		b += a;
	}
	cout << b << endl;   //print the answer

	return 0;
}
