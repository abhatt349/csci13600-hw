/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Genady Maryash
Assignment: HW 6.7
*/

//This function takes in an array of integers and its length
//as parameters and reverses the order of the elements
//in the array
//It doesn't return anything, it modifies the array
void reverse(int[] arr, int size) {
	int[size] rev;

	for (int i = 0; i < size; i++) {
		rev[i] = arr[size - i - 1];
	}

	for (int i = 0; i < size; i++) {
		arr[i] = rev[i];
	}
	return;
}
