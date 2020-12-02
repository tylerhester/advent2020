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
    unordered_map<float, float> expenseReport;

    ifstream report;
    report.open("expensereport.txt");

    string line;

    while (!report.eof() && getline(report, line)) {
        float expense = stof(line);
        expenseReport[expense] = 2020 - expense;
    }

    for (auto kv : expenseReport) {
        if (expenseReport.count(kv.second)) {
            cout << kv.first * kv.second << endl;
            break;
        }
    }

    report.close();

    return 0;
}
