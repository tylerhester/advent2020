#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool hasRequired(unordered_map<string, string>);
bool isValidPass(unordered_map<string, string>);
vector<string> splitString(string, string);

int main() {
    string line;
    ifstream corpus;
    int validPasses = 0;
    // corpus.open("testing4.txt");
    corpus.open("passports.txt");

    unordered_map<string, string> passport;
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
                passport[kv[0]] = kv[1];
            }
        }
    }

    // Check the last passport
    validPasses += isValidPass(passport);

    cout << "Part 1: " << validPasses << endl;
    corpus.close();
    return 0;
}

bool hasRequired(unordered_map<string, string> pass) {
    bool valid = pass.count("byr") && pass.count("iyr") && pass.count("eyr") && pass.count("hgt") && pass.count("hcl") && pass.count("ecl") && pass.count("pid");
    if ((pass.count("cid") && valid) || (!pass.count("cid") && valid))
        return true;
    return false;
}

bool isValidPass(unordered_map<string, string> pass) {
    bool valid = true;
    // Check byr
    string byr = pass["byr"];
    int birthyr = stoi(byr);
    
    // Check iyr
    string iyr = pass["iyr"];
    int issueyr = stoi(iyr);

    // Check eyr
    string eyr = pass["eyr"];
    int expireyr = stoi(eyr);

    // Check hgt
    // Get the number and the units


    // Check hcl
    // Check for # and alphanumeric in range


    // Check ecl
    // Check if valid from list


    // Check pid
    // Check if a 9 digit number


    if(byr.length() != 4 || iyr.length() != 4 || eyr.length() != 4)
        valid = false;
    if((birthyr < 1920 || birthyr > 2002) || (issueyr < 2010 || issueyr > 2020) || (expireyr < 2020 || expireyr > 2030))
        valid = false;

    return valid;
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

