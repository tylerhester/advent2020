#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

int main() {
    string row;
    ifstream file;
    vector<string> geology;
    // file.open("testing3.txt");
    file.open("map.txt");

    // Skip the first line
    getline(file, row);
    cout << row << endl;

    int hits = 0, rows = 1;
    while (getline(file, row) && !file.eof() && row.compare("")) {
        int pos = (3 * rows) % row.size();
        if (row[pos] == '#') {
            row[pos] = 'X'; 
            hits++;
        } else {
            row[pos] = 'O';
        }
        cout << row << endl;
        rows++;
    }

    cout << "Part 1: " << hits << endl;

    return 0;
}
