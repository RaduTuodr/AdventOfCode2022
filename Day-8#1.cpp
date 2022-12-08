#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int FOREST_MAX = 1e2 + 1;

int forest_height, forest_width;
int forest[FOREST_MAX][FOREST_MAX];

int visible_trees;
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

void solve() {

    visible[1][1] = visible[1][forest_width] = visible[forest_height][1] = visible[forest_height][forest_width] = 1;
    
    //top-down
    for (int j = 2; j <= forest_width - 1; j++) {

        int max_value = -1;

        for (int i = 1; i <= forest_height; i++)
            if (max_value < forest[i][j]) {
                
                visible[i][j] = true,
                max_value = forest[i][j];
            }
    }

    //bottom-up
    for (int j = 2; j <= forest_width - 1; j++) {

        int max_value = -1;

        for (int i = forest_height; i >= 1; i--)
            if (max_value < forest[i][j])
                visible[i][j] = true,
                max_value = forest[i][j];
    }

    //left-right
    for (int i = 2; i <= forest_height - 1; i++) {

        int max_value = -1;

        for (int j = 1; j <= forest_width; j++)
            if (max_value < forest[i][j])
                visible[i][j] = true,
                max_value = forest[i][j];
    }

    //left-right
    for (int i = 2; i <= forest_height - 1; i++) {

        int max_value = -1;

        for (int j = forest_width; j >= 1; j--)
            if (max_value < forest[i][j])
                visible[i][j] = true,
                max_value = forest[i][j];
    }

    for (int i = 1; i <= forest_height; i++)
        for (int j = 1; j <= forest_width; j++)
            visible_trees += visible[i][j];
}

void display() {

    fout << visible_trees;
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
