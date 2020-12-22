#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool hasRequired(unordered_map<string, string>);
bool isValidPass(unordered_map<string, string>);
void printPass(unordered_map<string, string>);
vector<string> splitString(string, string);

int main() {
    string line;
    ifstream corpus;
    int part1, part2 = 0;
    // corpus.open("testing4.txt");
    corpus.open("passports.txt");

    unordered_map<string, string> passport;
    while (getline(corpus, line) && !corpus.eof()) {
        // Check if empty line
        if (!line.compare("")) {
            // Check validity and start new passport
            if (hasRequired(passport)) {
                part1++;
                if (isValidPass(passport)) {
                    cout << "Valid > ";
                    part2++;
                } else {
                    cout << "Invalid > ";
                }
            } else {
                cout << "Req. Miss > ";
            }
            printPass(passport);
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
    part1 += (hasRequired(passport));
    part2 += (hasRequired(passport) && isValidPass(passport));
    cout << endl;

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;
    corpus.close();
    return 0;
}

void printPass(unordered_map<string, string> pass) {
    for (auto kv : pass) {
        cout << " " << kv.first << ": " << kv.second;
    }
    cout << endl;
}

bool hasRequired(unordered_map<string, string> pass) {
    bool valid = pass.count("byr") && pass.count("iyr") && pass.count("eyr") &&
                 pass.count("hgt") && pass.count("hcl") && pass.count("ecl") &&
                 pass.count("pid");
    // if ((pass.count("cid") && valid) || (!pass.count("cid") && valid))
    //    return true;
    return valid;
}

bool isValidPass(unordered_map<string, string> pass) {
    bool valid = true;
    try {
        // Check byr
        string byr = pass["byr"];
        int birthyr = stoi(byr);
        if (birthyr < 1920 || birthyr > 2002) return false;

        // Check iyr
        string iyr = pass["iyr"];
        int issueyr = stoi(iyr);
        if (issueyr < 2010 || issueyr > 2020) return false;

        // Check eyr
        string eyr = pass["eyr"];
        int expireyr = stoi(eyr);
        if (expireyr < 2020 || expireyr > 2030) return false;

        // Check hgt
        // Get the number and the units
        string hgt = pass["hgt"];
        string units = hgt.substr(hgt.length() - 2);
        string hStr = hgt.substr(0, hgt.length() - 2);
        int height = stoi(hgt.substr(0, hgt.length() - 2));
        if (!units.compare("cm")) {
            if (height < 150 || height > 193) return false;
        } else if (!units.compare("in")) {
            if (height < 59 || height > 76) return false;
        } else {
            return false;
        }

        // Check hcl
        // Check for # and alphanumeric in range
        string hcl = pass["hcl"];
        int hclPoundFound = hcl.find('#');
        // Pound is always at start of string so always 0
        if (!hclPoundFound) {
            string hairColor = hcl.substr(hclPoundFound + 1);
            if (hairColor.length() != 6) return false;
            if (!regex_match(hairColor, regex("^[a-f0-9]*$"))) return false;
        } else {
            return false;
        }

        // Check ecl
        // Check if valid from list
        string ecl = pass["ecl"];
        if (ecl.compare("amb") && ecl.compare("blu") && ecl.compare("brn") &&
            ecl.compare("gry") && ecl.compare("grn") && ecl.compare("hzl") &&
            ecl.compare("oth")) {
            return false;
        }

        // Check pid
        // Check if a 9 digit number
        string pid = pass["pid"];
        if (pid.length() != 9) return false;
        if (!regex_match(pid, regex("^[0-9]*$"))) return false;

    } catch (...) {
        return false;
    }
    return true;
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

