#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool isValidPass(unordered_map<string, bool>);
vector<string> splitString(string, string);

int main() {
    string line;
    ifstream corpus;
    int validPasses = 0;
    // corpus.open("testing4.txt");
    corpus.open("passports.txt");

    unordered_map<string, bool> passport;
    while (getline(corpus, line) && !corpus.eof()) {
        // Check if empty line
        if (!line.compare("")) {
            // Check validity and start new passport
            if (isValidPass(passport)) {
                validPasses++;
            }
            passport.clear();
        } else {
            // Process line and continue
            vector<string> kvs = splitString(line, " ");
            for (auto keyValue : kvs) {
                vector<string> kv = splitString(keyValue, ":");
                passport[kv[0]] = true;
            }
        }
    }

    // Check the last passport
    validPasses += isValidPass(passport);

    cout << "Part 1: " << validPasses << endl;
    corpus.close();
    return 0;
}

bool isValidPass(unordered_map<string, bool> pass) {
    bool valid = pass["byr"] && pass["iyr"] && pass["eyr"] && pass["hgt"] &&
                 pass["hcl"] && pass["ecl"] && pass["pid"];
    if ((pass["cid"] && valid) || (!pass["cid"] && valid))
        return true;
    else
        return false;
}

vector<string> splitString(string str, string delim) {
    vector<string> splitstr;
    int idx = str.find(delim);
    // -1 is true, make sure > 0
    while (idx > 0) {
        string split = str.substr(0, idx);
        splitstr.push_back(split);
        str = str.substr(idx + 1);
        idx = str.find(delim);
    }
    // Push back the rest of the line
    splitstr.push_back(str);
    return splitstr;
}

