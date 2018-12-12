/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Maryash
Assignment: Project1D

The program reads a sequence of ints and plus or minus signs  or squares and prints the evaluated result.
*/



#include <iostream>
using namespace std;

int line(int b) {
	char a;
	int sign = 1;
	int ans = 0;
	ans += b;
	while (cin >> a) {
		if (a == '^') {         //deals with the squares
			ans -= sign * b;
			ans += sign * b * b;
			cin >> a;
		}
		if (a == ';') {         //deals with muliple lines
			cout << ans << endl;
			return 0;
		}

		if (a == '+') {
			sign = 1;
		}
		if (a == '-') {
			sign = -1;
		}
		cin >> b;
		ans += sign * b;
	}
	cout << ans << endl;     //prints answer
	return 0;
}

int main() {
	int a;
	while (cin >> a) {
		line(a);
	}
	return 0;
}
