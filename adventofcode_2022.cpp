#include <iostream>
#include <fstream>
#include <map>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int WIN = 6;
const int DRAW = 3;
const int LOSS = 0;

const int FOR_A = 1;
const int FOR_B = 2;
const int FOR_C = 3;

long long total_score;
bool freq[256];
map<char, char> right_moves;

void read(char& their_move, char& my_move) {

    char line[4];

    fin.getline(line, 4);

    their_move = line[0];
    my_move = line[2];
}

char get_right_move(char their_move, char my_move) {

    if (their_move == 'A')
        if (my_move == 'X')
            return 'C';
        else if (my_move == 'Y')
            return 'A';
        else
            return 'B';
    
    else if (their_move == 'B')
        if (my_move == 'X')
            return 'A';
        else if (my_move == 'Y')
            return 'B';
        else
            return 'C';

    if (my_move == 'X')
        return 'B';
    else if (my_move == 'Y')
        return 'C';
    else
        return 'A';
}

int calculate_score(char their_move, char my_move) {

    if (their_move == 'A') // rock
        if (my_move == 'A')
            return FOR_A + DRAW;
        else if (my_move == 'B')
            return FOR_B + WIN;
        else
            return FOR_C + LOSS;

    else if (their_move == 'B') // paper
        if (my_move == 'A')
            return FOR_A + LOSS;
        else if (my_move == 'B')
            return FOR_B + DRAW;
        else
            return FOR_C + WIN;
    
    // if their_move is scissors (C)
    if (my_move == 'A')
        return FOR_A + WIN;
    else if (my_move == 'B')
        return FOR_B + LOSS;
    else
        return FOR_C + DRAW;
}

void solve() {

    char their_move, my_move;

    while (fin.eof() == false) {

        read(their_move, my_move);
        
        total_score += calculate_score(their_move, get_right_move(their_move, my_move));
    }
}

void display() {
    
    fout << total_score;
}

int main() {

    solve();
    display();

    fin.close();
    fout.close();

    return 0;
}