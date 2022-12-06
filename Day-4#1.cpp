#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int LINE_MAX = 2e8;

int no_pairs;
char line[LINE_MAX];
vector<pair<pair<int,int>, pair<int,int> > > pairs;

int counter;

int read_no(char line[], int& position) {

    int no_formed = 0;

    while (position < strlen(line) &&
           isdigit(line[position]))
        no_formed = no_formed * 10 + (line[position] - '0'),
        position++;

    return no_formed;
}

void read() {

    int position;
    int x1, y1;
    int x2, y2;

    while (fin.eof() == false) {

        fin.getline(line, LINE_MAX);
        position = 0;

        x1 = read_no(line, position);
        position++; /// skips '-'
        y1 = read_no(line, position);
        position++; /// skips ','
        x2 = read_no(line, position);
        position++; /// skips '-'
        y2 = read_no(line, position);

        pairs.push_back(make_pair(make_pair(x1, y1),
                                  make_pair(x2, y2)));
    }

    pairs.pop_back();
}

bool overlaps(pair<pair<int, int>, pair<int, int> > interval) {

    if (interval.first.first <= interval.second.first &&
        interval.first.second >= interval.second.second)
            return true;

    if (interval.first.first >= interval.second.first &&
        interval.first.second <= interval.second.second)
            return true;

    return false;
}

void solve() {

    for (size_t it = 0; it < pairs.size(); it++)
        if (overlaps(pairs[it]))
            counter++;
}

void display() {

    fout << counter;
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



