/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Genady Maryash
Assignment: HW 7.15
*/

#include <iostream>
using std::cout;
using std::endl;
using std::string;

int* read_data(int& size) {
	int input;
	int n = 10;
	int* arr = new int[n];
	int* tmp = new int[n];
	int counter = 0;
	while (cin >> input) {
		if (counter > n) {
			n *= 2;
			arr = new int[n];
			for (int i = 0; i < n / 2; i++) {
				arr[i] = tmp[i];
			}
			tmp = new int[n];
			for (int i = 0; i < n / 2; i++) {
				tmp[i] = arr[i];
			}
		}
		arr[counter] = input;
		tmp[counter] = input;
		counter++;
	}
	size = counter;
	int* finalArr = new int[size];
	for (int i = 0; i < size; i++) {
		finalArr[i] = arr[i];
	}
	free(arr);
	free(temp);
	return finalArr;
}
