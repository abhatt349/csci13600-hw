/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Genady Maryash
Assignment: HW 5.15
*/

#include <iostream>
using std::cout;
using std::endl;
using std::string;

int abs(int a) {
	if (a < 0) {
		return -1 * a;
	}
	return a;
}

int max(double a, double b) {
	return (int) ((a + b) + abs(a-b)) / 2;
}

int min(double a, double b) {
	return (int) ((a + b) - abs(a-b)) / 2;
}

int min(int a, int b, int c) {
	return min(min(a,b),c);
}

int max(int a, int b, int c) {
	return max(max(a,b),c);
}

void sort3(int& a, int& b, int& c) {
	int x, y, z;
	x = min(a, b, c);
	z = max(a, b, c);
	y = a + b + c - x - z;
	a = x;
	b = y;
	c = z;
	return;
}

int main() {
	int a = 3;
	int b = 2;
	int c = 1;
	cout << "a = " << a << endl << "b = " << b << endl << "c = " << c << endl << endl;
	sort3(c, b, a);
	cout << "a = " << a << endl << "b = " << b << endl << "c = " << c << endl << endl;
	sort3(a, b, c);
	cout << "a = " << a << endl << "b = " << b << endl << "c = " << c << endl << endl;
	sort3(c, b, a);
	cout << "a = " << a << endl << "b = " << b << endl << "c = " << c << endl << endl;
	sort3(a, c, b);
	cout << "a = " << a << endl << "b = " << b << endl << "c = " << c << endl << endl;
}
