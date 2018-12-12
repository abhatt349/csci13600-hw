/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Maryash
Assignment: Project1C

The program reads multiple sequences of ints and plus or minus signs and prints the evaluated results.
*/

#include <iostream>
using namespace std;

int line(int ans) {  //this function actually evaluates multiple lines;
	char a;
	int sign = 1;
	int b;
	while (cin >> a) {
		if (a == ';') {        //deals with multi-line input
			cout << ans << endl;
			return 0;
		}
		if (a == '+') {
			sign = 1;
		}
		else {
			sign = -1;
		}
		cin >> b;
		ans += (sign * b);
	}
	cout << ans << endl;
	return 0;
}

int main() {
	int a;
	while (cin >> a) {
		line(a);
	}
	return 0;
}
