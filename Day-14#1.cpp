#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int CAVE_MAX = 6e2;
const int LINE_MAX = 2e2;

int max_i_coord,
	max_j_coord;
int min_i_coord = CAVE_MAX,
	min_j_coord = CAVE_MAX;
char cave[CAVE_MAX][CAVE_MAX];
vector<vector<pair<int, int> > > lines;

int no_grains;

bool is_digit(char c);

pair<int, int> read_coord(char line[], size_t& position) {

	int j_coord = 0,
		i_coord = 0;

	while (is_digit(line[position]) == true)
		j_coord = j_coord * 10 + (line[position] - '0'),
		position++;

	position++; // skip the ','

	while (position < strlen(line) && is_digit(line[position]) == true)
		i_coord = i_coord * 10 + (line[position] - '0'),
		position++;

	if (max_j_coord < j_coord)
		max_j_coord = j_coord;
	if (max_i_coord < i_coord)
		max_i_coord = i_coord;

	if (min_j_coord > j_coord)
		min_j_coord = j_coord;
	if (min_i_coord > i_coord)
		min_i_coord = i_coord;

	return make_pair(j_coord, i_coord);
}

void read() {

	size_t line_index = 0,
		   position = 0;
	pair<int, int> coords;
	char line[LINE_MAX];

	while (fin.eof() == false) {

		fin.getline(line, LINE_MAX);
		position = 0;

		lines.push_back({});
		while (position < strlen(line)) {
		
			lines[line_index].push_back(read_coord(line, position));

			position += 4; // skip the ' -> '
		}
		++line_index;
	}

	/*
	for (size_t i = 0; i < lines.size(); i++, cout << endl)
		for (size_t j = 0; j < lines[i].size(); j++)
			cout << lines[i][j].first << "," << lines[i][j].second << " -> ";
	*/
}

void init_cave() {

	//for (int i = min_i_coord; i <= max_i_coord; i++)
	for (int i = 0; i <= max_i_coord + 2; i++)
		for (int j = 0; j <= max_j_coord + 2; j++)
			cave[i][j] = '.';
}

void place_lines() {

	for (size_t i = 0; i < lines.size(); i++)
		for (size_t j = 0; j < lines[i].size() - 1; j++) {

			pair<int, int> start_coords = lines[i][j],
						 end_coords = lines[i][j + 1];

			if (start_coords.first == end_coords.first) {
		
				int start = min(start_coords.second, end_coords.second),
					end = max(start_coords.second, end_coords.second);
				
				for (int k = start; k <= end; k++)
					cave[k][start_coords.first] = '#';
			} 
			else {

				int start = min(start_coords.first, end_coords.first),
					end = max(start_coords.first, end_coords.first);

				for (int k = start; k <= end; k++)
					cave[start_coords.second][k] = '#';
			}
		}
}

bool well_placed_grain() {

	pair<int, int> curr_coord = make_pair(500, 0),
				   old_coord;
	
	bool moved_left = false,
		moved_right = false;
	do {

		old_coord = curr_coord;

		if (cave[curr_coord.second + 1][curr_coord.first] == '.')
			curr_coord.second++;
		else if (cave[curr_coord.second + 1][curr_coord.first - 1] == '.')
			curr_coord.first--,
			curr_coord.second++;
		else if (cave[curr_coord.second + 1][curr_coord.first + 1] == '.')
			curr_coord.first++,
			curr_coord.second++;

	} while (old_coord != curr_coord || curr_coord.second == max_i_coord + 1);

	if (curr_coord.second > max_i_coord)
		return false;

	cave[curr_coord.second][curr_coord.first] = 'o';
	return true;
}

void place_sand() {

	while (well_placed_grain())
		;
}

void count_grains() {

	for (int i = 0; i <= 600; i++)
		for (int j = 0; j <= 600; j++)
			if (cave[i][j] == 'o')
				no_grains++;
}

void solve() {

	init_cave();
	place_lines();
	place_sand();
	count_grains();
}

void display() {

	
	for (int i = 0; i <= max_i_coord; i++, cout << endl)
	//for (int i = min_i_coord; i <= max_i_coord; i++, fout << endl)
		for (int j = min_j_coord; j <= max_j_coord; j++)
			cout << cave[i][j];
	
	fout << no_grains;
}

int main() {

	read();
	solve();
	display();

	fin.close();
	fout.close();

	return 0;
}

bool is_digit(char c) {

	return (c >= '0' && c <= '9');
}
