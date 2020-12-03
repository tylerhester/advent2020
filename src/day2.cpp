#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;

vector<string> splitString(string, char);
bool requiredInRange(string, string, int, int);
bool requiredInPosition(string, string, int, int);

int main() {
    string line;
    ifstream passwords;
    // passwords.open("testing2.txt");
    passwords.open("passwords.txt");

    int totalValidPass = 0;
    int totalValidPassPart2 = 0;
    while (getline(passwords, line) && !passwords.eof() && line.compare("")) {
        vector<string> requiredAndPass = splitString(line, ':');
        string required = requiredAndPass[0];
        string password = requiredAndPass[1];

        // Split left side to get min, max, and char
        vector<string> rangeAndChar = splitString(required, ' ');
        string range = rangeAndChar[0];
        string reqchar = rangeAndChar[1];

        vector<string> ranges = splitString(range, '-');
        int min = std::stoi(ranges[0]);
        int max = std::stoi(ranges[1]);

        totalValidPass += requiredInRange(password, reqchar, min, max);
        totalValidPassPart2 += requiredInPosition(password, reqchar, min, max);
    }

    cout << "Total Valid Passwords: " << totalValidPass << endl;
    cout << "Total Valid Passwords Part 2: " << totalValidPassPart2 << endl;

    return 0;
}

vector<string> splitString(string str, char delim) {
    vector<string> ret;
    int split = str.find(delim);
    string lside = str.substr(0, split);
    string rside = str.substr(split + 1);
    ret.push_back(lside);
    ret.push_back(rside);
    return ret;
}

bool requiredInRange(string password, string req, int min, int max) {
    int total = 0;
    for (auto c : password) {
        if (c == req[0]) total++;
    }
    return total >= min && total <= max;
}

bool requiredInPosition(string password, string req, int pos1, int pos2) {
    int total = (password[pos1] == req[0]) + (password[pos2] == req[0]);
    return total == 1;
}
