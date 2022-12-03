#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int ELVES_MAX = 1e4;
const int MAX_CALORIE_LENGTH = 10;

int no_elves;
int elve_calories[ELVES_MAX];
int maximum_no_calories;

int convert_chara_to_int(char calories[]) {

	int no_calories = 0;

	for (size_t i = 0; i < strlen(calories); i++)
		no_calories = no_calories * 10 + (calories[i] - '0');

	return no_calories;
}

void read() {

	char calories[MAX_CALORIE_LENGTH];

	while (fin.eof() == false) {

		no_elves++;

		do {

			fin.getline(calories, MAX_CALORIE_LENGTH);

			elve_calories[no_elves] += convert_chara_to_int(calories);

		} while (strcmp(calories, ""));
	}
}

void solve() {

	sort(elve_calories + 1, elve_calories + no_elves + 1);
}

void display() {

	fout << elve_calories[no_elves] +
		elve_calories[no_elves - 1] +
		elve_calories[no_elves - 2];
}

int main() {

	read();
	solve();
	display();

	fin.close();
	fout.close();

	return 0;
}
