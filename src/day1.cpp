#include <fstream>
#include <iostream>
#include <unordered_map>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;
using std::unordered_map;

int main() {
    unordered_map<int, int> expenseReport;

    ifstream report;
    report.open("data/expensereport.txt");

    string line;

    while (!report.eof() && getline(report, line) && line.compare("")) {
        int expense = stoi(line);
        expenseReport[expense] = 2020 - expense;
    }

    for (auto kv : expenseReport) {
        if (expenseReport[kv.second] == kv.first) {
            cout << kv.first * kv.second << endl;
            break;
        }
    }

    report.close();

    return 0;
}
