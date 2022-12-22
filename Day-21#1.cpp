#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

struct monkey_job {

	int value = 0;
	
	char operation;
	string factor1, factor2;
};

int root_value;
map<string, monkey_job> jobs;

bool is_digit(char c) {
	return ('0' <= c && c <= '9');
}

void read() {

	string monkey_name;
	int value;
	char operation;
	string factor1, factor2;

	string line;
	while (fin.eof() == false) {

		getline(fin, line);
		
		value = 0;
		factor1 = factor2 = "";
		operation = NULL;

		monkey_name = line.substr(0, 4); // get monkey name
		
		if (is_digit(line[6]) == true)
			value = stoi(line.substr(6));
		else {
			
			factor1 = line.substr(6, 4);
			operation = line[11];
			factor2 = line.substr(13, 4);
		}

		monkey_job job;
		job.value = value;
		job.factor1 = factor1;
		job.operation = operation;
		job.factor2 = factor2;

		jobs.insert({ monkey_name, job });
	}
}

int get_value_from_op(int factor1, int factor2, char operation) {

	if (operation == '+')
		return factor1 + factor2;
	else if (operation == '-')
		return factor1 - factor2;
	else if (operation == '*')
		return factor1 * factor2;

	return factor1 / factor2;
}

int get_monkey_value(string monkey_name) {

	monkey_job job = jobs[monkey_name];

	if (job.value == 0)
		return get_value_from_op(get_monkey_value(job.factor1), 
								 get_monkey_value(job.factor2), 
								 job.operation);
	return job.value;
}

void solve() {

	root_value = get_monkey_value("root");
}

void display() {

	fout << root_value;
}

int main() {

	read();
	solve();
	display();

	fin.close();
	fout.close();

	return 0;
}
