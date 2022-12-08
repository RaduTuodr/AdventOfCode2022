#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int FOREST_MAX = 1e2 + 1;

int forest_height, forest_width;
int forest[FOREST_MAX][FOREST_MAX];

int highest_score;
bool visible[FOREST_MAX][FOREST_MAX];

void read() {

    char line[FOREST_MAX];

    while (fin.eof() == false) {

        fin.getline(line, FOREST_MAX);

        forest_height++;
        for (size_t i = 0; i < strlen(line); i++)
            forest[forest_height][i + 1] = (line[i] - '0');
    }
    forest_width = (int)strlen(line);
}

bool inside(int i, int j) {

    return (i >= 1 && i <= forest_height && j >= 1 && j <= forest_width);
}

long long calculate_scenic_score(int i, int j) {

    int height = forest[i][j];
    int new_i, new_j;

    int up = 1, 
        down = 1,
        left = 1, 
        right = 1;

    //up
    new_i = i + 1;
    while (inside(new_i, j) && forest[new_i][j] < height)
        up++,
        new_i++;
    if (inside(new_i, j) == false)
        up--;

    //down
    new_i = i - 1;
    while (inside(new_i, j) && forest[new_i][j] < height)
        down++,
        new_i--;
    if (inside(new_i, j) == false)
        down--;

    //right
    new_j = j + 1;
    while (inside(i, new_j) && forest[i][new_j] < height)
        right++,
        new_j++;
    if (inside(i, new_j) == false)
        right--;

    //left
    new_j = j - 1;
    while (inside(i, new_j) && forest[i][new_j] < height)
        left++,
        new_j--;
    if (inside(i, new_j) == false)
        left--;

    return up * down * right * left;
}

void solve() {

    for (int i = 1; i <= forest_height; i++)
        for (int j = 1; j <= forest_width; j++) {
         
            long long score = calculate_scenic_score(i, j);
            
            if (score > highest_score)
                highest_score = score;
        }
}

void display() {

    fout << highest_score;
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
