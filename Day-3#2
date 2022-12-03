#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int _MAX = 3e2 + 1;
const int ALPH_SIZE = 26;
const int ASCII_SIZE = 256;

int no_rucksacks;
string rucksack_items[_MAX];

bool container1_freq[ASCII_SIZE];
bool container2_freq[ASCII_SIZE];
bool container3_freq[ASCII_SIZE];

int total_priority;

void read() {
    
    while (fin.eof() == false)
        fin >> rucksack_items[++no_rucksacks];
}

void init(bool arr[]) {

    for (int i = 'A'; i <= 'z'; i++)
        arr[i] = false;
}

void set_freq(string str, bool arr[], int left, int right) {

    for (int i = left; i < right; i++)
        arr[int(str[i])] = true;
}

char check_for_both() {

    for (int i = 'A'; i <= 'z'; i++)
        if (container1_freq[i] && container2_freq[i] && container3_freq[i])
            return i;

    return '0';
}

int convert_char_to_priority(char id_char) {

    if ('a' <= id_char && id_char <= 'z')
        return (int)id_char - 'a' + 1;
    return (int)id_char - 'A' + ALPH_SIZE + 1;
}

void solve() {

    for (int i = 1; i <= no_rucksacks; i += 3) {

        string item1 = rucksack_items[i];
        string item2 = rucksack_items[i + 1];
        string item3 = rucksack_items[i + 2];

        init(container1_freq);
        init(container2_freq);
        init(container3_freq);

        set_freq(item1, container1_freq, 0, item1.size());
        set_freq(item2, container2_freq, 0, item2.size());
        set_freq(item3, container3_freq, 0, item3.size());

        char id_char = check_for_both();

        total_priority += convert_char_to_priority(id_char);
    }
}

void display() {
    
    fout << total_priority;
}

int main() {

    read();
    solve();
    display();

    fin.close();
    fout.close();

    return 0;
}
