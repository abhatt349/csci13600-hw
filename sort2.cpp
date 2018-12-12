/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Genady Maryash
Assignment: HW 5.14
*/

#include <iostream>
using std::cout;
using std::endl;
using std::string;

void sort2(int& a, int& b) {
	if (a > b) {
		int c = a;
		a = b;
		b = c;
	}
	return;
}


int main() {
	int a = 10;
	int b = 5;

	cout << "a = " << a << endl << "b = " << b << endl;
	sort2(b, a);
	cout << "a = " << a << endl << "b = " << b << endl;
	sort2(a, b);
	cout << "a = " << a << endl << "b = " << b << endl;
	return 0;
}
