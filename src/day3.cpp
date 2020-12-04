#include <fstream>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::unordered_map;
using std::vector;

typedef std::numeric_limits<double> dbl;

// In order to use vector as key in hashmap
// We need to define the hasher
struct hashVector {
    int operator()(const vector<int>& vect) const {
        int hash = vect.size();
        for (auto& i : vect) {
            hash ^= vect[i];
        }
        return hash;
    }
};

int main() {
    string row;
    ifstream file;
    vector<string> geology;
    unordered_map<vector<int>, int, hashVector> tobogganPerf;
    file.open("testing3.txt");
    // file.open("map.txt");

    vector<int> slope = {1, 2};
    tobogganPerf[slope] = 0;
    slope = {3, 1};
    // tobogganPerf[slope] = 0;
    slope = {5, 1};
    // tobogganPerf[slope] = 0;
    slope = {7, 1};
    // tobogganPerf[slope] = 0;
    slope = {1, 2};
    // tobogganPerf[slope] = 0;

    // y = mx
    getline(file, row);
    cout << row << endl;

    int m = 0;
    int x = 1;
    while (getline(file, row) && !file.eof() && row.compare("")) {
        for (auto kv : tobogganPerf) {
            int m = kv.first[0];
            if (kv.first[1] == 1) {
                int y = (m * x) % row.size();
                if (row[y] == '#') {
                    if (row[y] == '#') {
                        tobogganPerf[kv.first] = kv.second + 1;
                        row[y] = 'X';
                    } else {
                        row[y] = 'O';
                    }
                } 
            } else if (kv.first[1] == 2) {
                int y = (m * x) % row.size();
                if (!(x % 2)) {
                    if (row[y] == '#') {
                        tobogganPerf[kv.first] = kv.second + 1;
                        row[y] = 'X';
                    } else {
                        row[y] = 'O';
                    }
                }
            }
        }
        // Debugging
        cout << row << endl;
        x++;
    }

    slope = {1, 2};
    cout << "Part 1: " << tobogganPerf[slope] << endl;

    double part2 = 1;
    for (auto kv : tobogganPerf) {
        part2 *= kv.second;
    }
    cout.precision(dbl::max_digits10);
    cout << "Part 2: " << part2 << endl;
    return 0;
}
