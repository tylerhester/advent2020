#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

typedef std::numeric_limits<double> dbl;

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::unordered_map;
using std::vector;

bool sumOfTwo(vector<double>, double);

int main(int argc, char *argv[]) {
    ifstream file;
    // file.open("input/testing9.txt");
    file.open("input/day9input.txt");

    vector<double> data;

    string line;
    while (getline(file, line)) {
        data.push_back(std::stod(line));
    }

    int preambleLen = 25;
    // int preambleLen = 25;

    // Starting after the preamble call sumOfTwo on each number with the
    // "preamble" length numbers before it
    for (int i = preambleLen; i < data.size(); i++) {
        vector<double> nums(data.begin() + i - preambleLen, data.begin() + i);
        if (!sumOfTwo(nums, data[i])) {
            cout << "Part 1 > " << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << data[i] << endl;
            break;
        }
    }

    return 0;
}

// Check if val is the sum of two of the numbers within nums
bool sumOfTwo(vector<double> nums, double val) {
    unordered_map<double, double> differences;

    for (auto num : nums) {
        differences[num] = val - num;
    }

    for (auto kv : differences) {
        if (differences.find(kv.second) != differences.end()) {
            return true;
        }
    }

    return false;
}
