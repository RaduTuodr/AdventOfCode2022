#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int MAX_DIR = 1e4;
const int MAX_LINE = 256;
const int MAX_DIR_MEMORY = 1e5;

struct file {

    int size;
    string title;
};

struct directory {

    string title;
    vector<file> files;
};

int no_directories;
string directory_titles[MAX_DIR];
map<string, string> fathers;
map<string, directory> directories;
map<string, vector<string> > edges; // relationships between directories

vector<string> end_dir;
map<string, long long> directory_size;
long long total_size;

bool is_digit(char c) {

    return (c >= '0' && c <= '9');
}

file read_file(char line[]) {

    file read_file;

    int index = 0;
    int size = 0;
    string title = "";

    while (is_digit(line[index]) == true)
        size = size * 10 + (line[index++] - '0');

    for (int it = index + 1; it < strlen(line); it++)
        title += line[it];

    read_file.size = size;
    read_file.title = title;

    return read_file;
}

directory read_directory(char line[]) {

    directory dir;
    string title = "";

    for (int it = 4; it < strlen(line); it++)
        title += line[it];

    dir.title = title;
    dir.files = {};

    return dir;
}

string get_dir_title(char line[]) {

    string dir_title = "";

    for (int it = 5; it < strlen(line); it++)
        dir_title += line[it];

    return dir_title;
}

void read() {

    bool unread = false;
    char line[MAX_LINE];
    string curr_directory;

    // add base directory
    directory_titles[++no_directories] = "/";
    directory_size["/"] = 0;

    while (fin.eof() == false) {

        if (unread == false)
            fin.getline(line, MAX_LINE);
        else
            unread = false;

        if (line[0] == '$') {

            if (line[2] == 'c') {
                
                if (get_dir_title(line) != "..")
                    curr_directory = get_dir_title(line);
                else
                    curr_directory = fathers[curr_directory];
            }
            else if (line[2] == 'l') {

                do {

                    fin.getline(line, MAX_LINE);

                    if (strcmp(line, "") && line[0] != '$') {

                        if (line[0] == 'd') { // check for directory 
                        
                            directory read_dir = read_directory(line);

                            directory_titles[++no_directories] = read_dir.title;
                            directory_size[read_dir.title] = 0;
                            fathers[read_dir.title] = curr_directory;
                            edges[curr_directory].push_back(read_dir.title);

                        } else if (is_digit(line[0])) {

                            file read_fl = read_file(line);

                            directories[curr_directory].files.push_back(read_fl);
                        }
                    }
                    else
                        unread = true;

                } while (strcmp(line, "") && fin.eof() == false && line[0] != '$');
            }
        }
    }
}

int depth_first_search(string direc) { // calculate each directory size using dfs starting 
                                    // from base directory "/"

    string neighbour;

    for (size_t i = 0; i < edges[direc].size(); i++)
        neighbour = edges[direc][i],
        directory_size[direc] += depth_first_search(neighbour);

    for (size_t i = 0; i < directories[direc].files.size(); i++)
        directory_size[direc] += directories[direc].files[i].size;

    return directory_size[direc];
}

void depth_first_search_for_end_dir(string direc) {

    string neighbour;

    for (size_t i = 0; i < edges[direc].size(); i++)
        depth_first_search_for_end_dir(edges[direc][i]);

    if (edges[direc].size() == 0)
        end_dir.push_back(direc);
}

void calculate_memory_sizes() {

    for (int i = 1; i <= no_directories; i++) {

        string directory_title = directory_titles[i];

        for (size_t it = 0; it < directories[directory_title].files.size(); it++)
            directory_size[directory_title] += directories[directory_title].files[it].size;
    }

    for (size_t i = 0; i < end_dir.size(); i++) {

        string curr_dir = end_dir[i];

        do {

            for (size_t i = 0; i < edges[curr_dir].size(); i++)
                directory_size[curr_dir] += directory_size[edges[curr_dir][i]];

            curr_dir = fathers[curr_dir];
            
        } while (curr_dir != "/");
    }
}

void solve() {

    //directory_size["/"] = depth_first_search("/");  ~~~ stack overflow because of large input :(

    depth_first_search_for_end_dir("/");
    calculate_memory_sizes();

    for (int i = 1; i <= no_directories; i++)
        if (directory_size[directory_titles[i]] <= MAX_DIR_MEMORY)
            total_size += directory_size[directory_titles[i]];
}

void display() {
    
    fout << total_size;
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
