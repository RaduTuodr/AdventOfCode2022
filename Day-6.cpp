#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int ASCII_MAX = 256;
const int SIGNAL_LENGTH = 4;
// const int SIGNAL_LENGTH = 14; for the second part

string signal;
int freq[ASCII_MAX];
queue<char> current_signal;

size_t marker;

void read() {

    fin >> signal;
}

void solve() {

    size_t position = 0;
    bool found = false;
    int all_uniq = 0;

    for (position = 0; position < SIGNAL_LENGTH - 1; position++) {
        current_signal.push(signal[position]);

        if (freq[signal[position]] == 0)
            all_uniq++;

        freq[signal[position]]++;
    }

    while (found == false) {

        if (freq[signal[position]] == 0 && all_uniq == SIGNAL_LENGTH - 1)
            found = true,
            marker = position + 1;
        else {

            if (freq[signal[position]] == 0)
                all_uniq++;
            freq[signal[position]]++;
            current_signal.push(signal[position]);

            if (freq[current_signal.front()] == 1)
                all_uniq--;
            freq[current_signal.front()]--;
            current_signal.pop();
        }

        position++;
    }
}

void display() {

    fout << marker;
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
