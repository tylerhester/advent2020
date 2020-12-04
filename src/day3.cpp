#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

typedef std::numeric_limits<double> dbl;

double getPerf(vector<int>, vector<string>);

int main() {
    string row;
    ifstream file;
    vector<string> geology;
    vector<vector<int>> toboggans;
    // file.open("testing3.txt");
    file.open("map.txt");

    vector<int> slope = {1, 1};
    toboggans.push_back(slope);
    slope = {3, 1};
    toboggans.push_back(slope);
    slope = {5, 1};
    toboggans.push_back(slope);
    slope = {7, 1};
    toboggans.push_back(slope);
    slope = {1, 2};
    toboggans.push_back(slope);

    while (getline(file, row) && !file.eof() && row.compare("")) {
        geology.push_back(row);
    }

    cout << "Printing map..." << endl;
    for(auto row : geology)
        cout << row << endl;
    cout << endl;

    cout << "Part 1: " << getPerf(toboggans[1], geology) << endl;
    
    double total = 1;
    for (auto toboggan : toboggans) {
        total *= getPerf(toboggan, geology);
    
    }
    cout.precision(dbl::max_digits10);
    cout << "Part 2: " << total << endl;

    file.close();
    return 0;
}

double getPerf(vector<int> toboggan, vector<string> geology) {
    double totalHits = 0;
    int x = 0;
    for (int row = 0; row < geology.size(); row+=toboggan[1], x++) {
        int y = (x * toboggan[0]) % geology[row].length(); 
        if (geology[row][y] == '#') {
            totalHits++;
            geology[row][y] = 'X';
        } else {
            geology[row][y] = 'O';
        }
        // cout << geology[row] << endl;
    }
    return totalHits;
}
