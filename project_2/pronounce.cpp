/*
Author: Aryan Bhatt
Course: CSCI-135
Instructor: Gennadiy Maryash
Assignment: Project_2
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <string>
using std::string;

void cap(string& in) {
	for (int i = 0; i < in.length(); i++) {
		if (in.at(i) <= 'z' && in.at(i) >= 'a') {
			in.at(i) = in.at(i) - 'a' + 'A';
		}
		else {
			in.at(i) = in.at(i);
		}
	}
}

void splitOnSpace(string s, string & before, string & after) {
  // reset strings
  before = "";
  after = "";
  // accumulate before space
  int i = 0;
  while (i < s.size() && not isspace(s[i])) {
		before += s[i];
		i++;
	}
  // skip the space
  i++;
  // accumulate after space
  while (i < s.size()) {
		after += s[i];
		i++;
	}
}

bool isValid(string s) {
	for (int i = 0; i < s.length(); i++) {
		 if (!((s[i] >= 'A' && s[i] <= 'Z') || s[i] == '\'' || s[i] == ' ' || (s[i] >= '0' && s[i] <= '9'))) {
			 //std::cout << s << std::endl;
			 return false;
		 }
	}
	return true;
}

bool checker1(string first, string mem, string sec) {
	string memarr[100]; //array holding the phonemes in mem
	string secarr[100]; //array holding the phonemes in sec
	int i = 0;
	//populate memarr
	while (mem != "") {
		splitOnSpace(mem, memarr[i++], mem);
	}
	//keep track of the length of memarr/secarr
	int len = i;
	i = 0;
	//populate secarr
	while (sec != "") {
		splitOnSpace(sec, secarr[i++], sec);
	}
	if (len != i) {
		return false;
	}
	int issues = 0;
	for (i = 0; i < len; i++) {
		if (memarr[i] != secarr[i]) {
			issues++;
		}
	}
	return (issues == 1);
}

bool checker2(string first, string mem, string sec) {
	string memarr[100];
	string secarr[100];
	int i = 0;
	while (mem != "") {splitOnSpace(mem, memarr[i++], mem);} //populates memarr
	int len = i;
	i = 0;
	while (sec != "") {splitOnSpace(sec, secarr[i++], sec);} //populates secarr
	if (i != len + 1) {return false;}
	i = len - 1;
	while (memarr[i] == secarr[i+1]) {
		i--;
	}
	int j = 0;
	while (memarr[j] == secarr[j]) {
		j++;
	}
	return (j == i + 1);
}


int main() {
	//std::cout << "Please enter a word: ";
	string ans;
	std::cin >> ans;
	cap(ans);
	std::ifstream fin("cmudict.0.7a");
  if (fin.fail()) {
    std::cerr << "File cannot be opened for reading." << std::endl;
		exit(1); // exit if failed to open the file
	}
	string line;  //line to read into
	string first; //first word
	string second;//pronunciation
	string mem = "";
	while(getline(fin, line)) {
		if (isValid(line)) {
			splitOnSpace(line, first, second);
			if (first == ans) {
				std::cout << "Pronunciation\t: " << second << '\n';
				mem = second;
			}
		}
	}
	if (mem == "") {
		std::cout << "Not found" << '\n';
		return 0;
	}
	std::cout << std::endl;
	fin.clear();
	fin.seekg(0, fin.beg);
	std::cout << "Identical\t: ";
	line = "";
	first = "";
	second = "";
	while(getline(fin, line)) {
		if (isValid(line)) {
			splitOnSpace(line, first, second);
			if (mem == second && first != ans) {
				std::cout << first << " ";
			}
		}
	}
	std::cout << std::endl;
	fin.clear();
	fin.seekg(0, fin.beg);
	std::cout << "Replace phoneme\t: ";
	line = "";
	first = "";
	second = "";
	while(getline(fin,line)) {
		if (isValid(line)) {
			splitOnSpace(line, first, second);
			if (checker1(first, mem, second)) {
				std::cout << first << " ";
			}
		}
	}
	std::cout << std::endl;
	fin.clear();
	fin.seekg(0, fin.beg);
	std::cout << "Add phoneme\t: ";
	line = "";
	first = "";
	second = "";
	while(getline(fin,line)) {
		if (isValid(line)) {
			splitOnSpace(line, first, second);
			if (checker2(first, mem, second)) {
				std::cout << first << " ";
			}
		}
	}
	std::cout << std::endl;
	fin.clear();
	fin.seekg(0, fin.beg);
	std::cout << "Remove phoneme\t: ";
	line = "";
	first = "";
	second = "";
	while(getline(fin,line)) {
		if (isValid(line)) {
			splitOnSpace(line, first, second);
			if (checker2(first, second, mem)) {
				std::cout << first << " ";
			}
		}
	}
	fin.close();
	return 0;
}
