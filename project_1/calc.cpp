/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Maryash
Assignment: Project1B

The program reads a sequence of ints and plus or minus signs and prints the evaluated result.
*/

#include <iostream>
using namespace std;

int main() {
	char a;
	int sign = 1; //keeps track of sign (+ or -)
	int b;
	int ans = 0;
	cin >> ans;
	while (cin >> a) {
		if (a == '+') {
			sign = 1;
		}
		else {
			sign = -1;
		}
		cin >> b;
		ans = ans + (sign * b);
	}
	cout << ans << endl;
	return 0;
}
