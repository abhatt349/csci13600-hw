/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Genady Maryash
Assignment: HW 5.16
Zeller Congruence to determine day of week
*/

#include <iostream>
using std::cout;
using std::endl;
using std::string;

string zeller_congruence(int d, int mm, int year) {
	if (mm == 13 || mm == 14) {
		year--;
	}

	int w = (d + 5 + ((26 * (mm + 1)) / 10) + ((5 * (year % 100)) / 4) + ((21 * (year / 100)) / 4)) % 7;
	string days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	return days[w];
}

int main (){
	// prints the days of the week of the last ten Christmases
	for (int year = 2017; year > 2007; year--) {
		cout << "In the year " << year << ", Christmas fell on a " << zeller_congruence(25, 1, year) << endl;
	}
	int ctr = 0;


	return 0;
}


/*
zmonth = ((month + 9) % 12) + 3;  <- maps normal months to zeller months
month = month - 12 * (month / 13); <- maps zeller months to normal months
*/
