#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>
#include <iomanip>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int Y_MAX = 5e1;
const int X_MAX = 2e2;
int di[4] = { -1, 0, 1, 0 };
int dj[4] = { 0, 1, 0, -1 };

int start_i,
    start_j;
int end_i,
    end_j;

int height,
    width;
int elevation[Y_MAX][X_MAX];
int trace[Y_MAX][X_MAX];

queue<pair<int, int> > Q;

void read() {
    
    char line[X_MAX];

    while (fin.eof() == false) {

        height++;
        fin.getline(line, X_MAX);

        for (size_t i = 0; i < strlen(line); i++)
            if (line[i] == 'S')
                start_j = i + 1,
                start_i = height,
                elevation[height][i + 1] = 0;
            else if (line[i] == 'E')
                end_j = i + 1,
                end_i = height,
                elevation[height][i + 1] = 'z' - 'a';
            else
                elevation[height][i + 1] = line[i] - 'a';
    }

    width = strlen(line);
}

bool valid(int i, int j) {

    if (i < 1 || j < 1 || i > height || j > width)
        return false;
    return true;
}

void lee(int start_i, int start_j) {

    Q.push(make_pair(start_i, start_j));

    while (Q.empty() == false) {

        int curr_i = Q.front().first;
        int curr_j = Q.front().second;

        Q.pop();

        for (int k = 0; k < 4; k++) {

            int new_i = curr_i + di[k];
            int new_j = curr_j + dj[k];

            if (valid(new_i, new_j) && trace[new_i][new_j] == 0
                &&
                elevation[new_i][new_j] <= elevation[curr_i][curr_j] + 1)
                trace[new_i][new_j] = trace[curr_i][curr_j] + 1,
                Q.push(make_pair(new_i, new_j));
        }
    }
}

void solve() {

    lee(start_i, start_j);
}

void display() {

    fout << trace[end_i][end_j];
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
