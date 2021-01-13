#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int partOne(string, unordered_map<string, vector<tuple<string, int>>> rules, unordered_map<string, bool>& memo);
bool canContainBag(string bag, string searchBag, unordered_map<string, vector<tuple<string, int>>> rules, unordered_map<string, bool>& memo);
vector<string> splitStr(string, string);

int main(int argc, char* argv[]) {
    ifstream file;
    //file.open("testing7.txt");
    file.open("luggage.txt");
    unordered_map<string, vector<tuple<string, int>>> luggageRules;
    unordered_map<string, bool> memo;

    string line;
    while (getline(file, line)) {
        vector<string> bagsAndContents = splitStr(line, " bags contain ");  // Get the Bag and what it can hold

        string bagColor = bagsAndContents[0];  // Get the Bag
        vector<tuple<string, int>> contains;   // Set of bag names and the amount that can be held by bagColor

        string containsBags = bagsAndContents[1];  // Get what it can hold
        vector<string> canHoldBags = splitStr(containsBags.substr(0, containsBags.length() - 1), ", ");

        // For each bag that can be held in bagColor get the color of the bag
        // and the amount
        for (auto bagAndAmount : canHoldBags) {
            if (bagAndAmount.substr(0, 2).compare("no")) {
                int amount = (int)bagAndAmount[0] - 48;
                string bagColor = bagAndAmount.substr(2, bagAndAmount.find("bag") - 3);
                contains.push_back(make_tuple(bagColor, amount));
            }
        }
        luggageRules.insert(make_pair(bagColor, contains));  // Add [bagColor, contains] to luggageRules
    }

    ;
    cout << "Part 1 > " << endl << partOne("shiny gold", luggageRules, memo) << endl;
    cout << "Part 2 > " << "" << endl;

    file.close();
    return 0;
}


/*
bool canContainBag(string bag, string searchBag, unordered_map<string, vector<tuple<string, int>>> rules, unordered_map<string, bool>& memo) {
    cout << "Searching " << bag << endl;
    bool doesContain = true;
    vector<tuple<string, int>> contents = rules[bag];
    if (contents.size() == 0) {
        memo[bag] = false;
        return !doesContain;
    } else if (contents.size() == 1) {
        if (!get<0>(contents[0]).compare(searchBag)) {
            memo[bag] = true;
            return doesContain;
        } else {
            return !doesContain;
        }
    } else {
        cout << "Checking ";
        for (auto& tuple : contents) {
            cout << get<0>(tuple) << ", ";
            if (!get<0>(tuple).compare(searchBag)) {
                doesContain = true;
                break;
            } else {
                if (memo.find(get<0>(tuple)) != memo.end()) {
                    doesContain = memo[get<0>(tuple)];
                    if (doesContain) break;
                } else {
                    doesContain = canContainBag(get<0>(tuple), searchBag, rules, memo);
                }
            }
        }
        cout << endl;
        memo[bag] = doesContain;
        return doesContain;
    }
}
*/

int partOne(string search, unordered_map<string, vector<tuple<string, int>>> rules, unordered_map<string, bool>& memo) {
    int result = 0;
    for(auto kv : rules) {
        string bagColor = kv.first;
        vector<tuple<string, int>> contents = kv.second;
        if (canContainBag(bagColor, search, rules, memo)) { 
            result++;
        } else {
        }
        cout << endl;
    }
    return result;
}

vector<string> splitStr(string str, string delim) {
    vector<string> ret;
    int idx = str.find(delim);
    while (idx > 0) {
        string split = str.substr(0, idx);
        ret.push_back(split);
        str = str.substr(idx + delim.length());
        idx = str.find(delim);
    }
    ret.push_back(str);
    return ret;
}

