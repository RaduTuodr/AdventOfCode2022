#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int FILE_MAX = 5e3 + 1;

struct node {

    int value;
    int index;
    node* left_node;
    node* right_node;

} * first, * last;

void create(node*& first, node*& last, int value) {

    first->value = value;
    last->value = value;
    first->index = 1;
    last->index = 1;

    first->left_node = last;
    first->right_node = last;

    last->left_node = first;
    last->right_node = first;
}

void add_to_right(node*& first, node*& last, int value, int index) {

    node* new_node = new node;

    new_node->left_node= last;
    new_node->right_node = first;

    new_node->value= value;
    new_node->index = index;

    last->right_node = new_node;
    last = new_node;

    first->left_node = last;
}

void insert_to_right(node* left_node, int value, int index) {

    node* new_node = new node;

    node* right_node = left_node->right_node;

    new_node->value = value;
    new_node->index = index;
    new_node->left_node = left_node;
    new_node->right_node = right_node;

    left_node->right_node = new_node;
    right_node->left_node = new_node;
}

node* get_node_to_left(node* the_node) {

    node* current_node = the_node;

    for (int i = 0; i <= -the_node->value; i++)
        current_node = current_node->left_node;

    return current_node;
}

node* get_node_to_right(node* the_node) {

    node* current_node = the_node;

    for (int i = 1; i <= the_node->value; i++)
        current_node = current_node->right_node;

    return current_node;
}

node* get_node_by_index(int index) {

    node* current_node = first;

    do {

        if (current_node->index == index)
            return current_node;

        current_node = current_node->right_node;

    } while (current_node != first);

    return NULL;
}

void hide_node(node* node_to_hide) {

    node_to_hide->left_node->right_node = node_to_hide->right_node;
    node_to_hide->right_node->left_node = node_to_hide->left_node;

    node_to_hide->index = -1;
}

void move_value_in_array(int index) {

    node* node_to_move = get_node_by_index(index);
    hide_node(node_to_move);

    node* left_node;

    if (node_to_move->value < 0)
        left_node = get_node_to_left(node_to_move);
    else
        left_node = get_node_to_right(node_to_move);

    insert_to_right(left_node, node_to_move->value, index);
}

node* get_node_past_k(node* first, int k) {

    node* current_node = first;

    for (int i = 1; i <= k; i++)
        current_node = current_node->right_node;

    return current_node;
}

int coords_size;
int coords[FILE_MAX];

int coord_0;
int grove_coordinates;

void read() {

    fin >> coords[++coords_size];
    create(first, last, coords[coords_size]);

    while (fin.eof() == false) {

        fin >> coords[++coords_size];
        
        add_to_right(first, last, coords[coords_size], coords_size);
    
        if (coords[coords_size] == 0)
            coord_0 = coords_size;
    }
}

void solve() {

    for (int i = 1; i <= coords_size; i++)
        if (coords[i])
            move_value_in_array(i);

    node* node_0 = get_node_by_index(coord_0);

    grove_coordinates += get_node_past_k(node_0, 1000 % coords_size)->value;
    grove_coordinates += get_node_past_k(node_0, 2000 % coords_size)->value;
    grove_coordinates += get_node_past_k(node_0, 3000 % coords_size)->value;
}

void display() {

    fout << grove_coordinates;
}
            
int main() {

    first = last = new node;

    read();
    solve();
    display();

    fin.close();
    fout.close();

    return 0;
}
