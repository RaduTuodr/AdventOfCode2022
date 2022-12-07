#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <queue>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int MAX_LINE = 256;
const int MAX_STACKS = 1e2;

int no_stacks;
deque<char> stack_crates[MAX_STACKS];
vector<pair<int, pair<int, int> > > querries;

bool is_digit(char c) {

    return (c <= '9' && c >= '0');
}

char read_crate(char line[], int& position) {

    char crate_char;
    crate_char = line[position + 1];

    position += 4;

    return crate_char;
}

pair<int, pair<int, int> > read_querry(char line[]) {

    int position = 5; /// start from index
    int index, from, to;

    index = 0;
    while (position < strlen(line) && is_digit(line[position]) == true)
        index = index * 10 + (line[position++] - '0');

    position += 6;

    from = 0;
    while (position < strlen(line) && is_digit(line[position]) == true)
        from = from * 10 + (line[position++] - '0');

    position += 4;

    to = 0;
    while (position < strlen(line) && is_digit(line[position]) == true)
        to = to * 10 + (line[position++] - '0');

    return make_pair(index, make_pair(from, to));
}

void read() {

    int position;
    char crate_index;
    char line[MAX_LINE];

    while (true) { /// we quit when we got the indexation line

        fin.getline(line, MAX_LINE - 1);

        if (is_digit(line[1]) == true)
            break;

        position = 0;

        while (position < strlen(line)) {

            crate_index = read_crate(line, position);
            if (crate_index != ' ')
                stack_crates[position / 4].push_back(crate_index);
        }
    }
    no_stacks = (strlen(line) + 1) / 4;

    fin.getline(line, MAX_LINE);

    while (fin.eof() == false) {

        fin.getline(line, MAX_LINE);
        querries.push_back(read_querry(line));
    }
}

void solve() {

    pair<int, pair<int, int> > querry;
    int index, from, to;

    for (size_t it = 0; it < querries.size(); it++) {

        querry = querries[it];
        index = querry.first;
        from = querry.second.first;
        to = querry.second.second;

        queue<char> move_stack;
        for (int i = 1; i <= index; i++)
            move_stack.push(stack_crates[from].front()),
            stack_crates[from].pop_front();

        while (move_stack.empty() == false)
            stack_crates[to].push_front(move_stack.front()),
            move_stack.pop();
    }
}

void display() {

    for (int it = 1; it <= no_stacks; it++) {

        char last_item;

        while (stack_crates[it].empty() == false)
            last_item = stack_crates[it].back(),
            stack_crates[it].pop_back();

        fout << last_item;
    }
}

int main()
{
    read();
    solve();
    display();

    fin.close();
    fout.close();

    return 0;
}
