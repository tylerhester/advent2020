#include <fstream>
#include <iostream>
#include <limits>
#include <unordered_map>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;
using std::unordered_map;

typedef std::numeric_limits< double > dbl;

void setDifference(double, unordered_map<double, double>&);
double findComplementTwo(double, unordered_map<double, double>);
double findComplementThree(double, unordered_map<double, double>);

int main() {
    unordered_map<double, double> expenseReport;

    ifstream report;
    // report.open("testing.txt");
    report.open("expensereport.txt");

    // Read in the file
    string line;
    while (!report.eof() && getline(report, line)) {
        double expense = stof(line);
        expenseReport[expense] = 0;
    }

    // Part and Part 2
    cout.precision(dbl::max_digits10);
    cout << "Part 1: " << findComplementTwo(2020, expenseReport) << endl;
    cout << "Part 2: " << findComplementThree(2020, expenseReport) << endl;

    report.close();

    return 0;
}

void setDifference(double val, unordered_map<double, double>& umap) {
    for (auto kv : umap)
        umap[kv.first] = val - kv.first;
}

double findComplementTwo(double val, unordered_map<double, double> umap) {
    double ans = 0.0;
    
    setDifference(val, umap);
    
    for(auto kv : umap) {
        if (umap.count(kv.second)) {
            ans = kv.first * kv.second; 
            break;
        }
    }
    return ans;
}

double findComplementThree(double val, unordered_map<double, double> umap) {
    double ans = 0.0;
    unordered_map<double, double> original = umap;
    setDifference(val, umap);

    for (auto kv: umap) {
        unordered_map<double, double> tmp = original;

        // Do you need to delete the key before searching again?
        double key = kv.first;
        double val = kv.second;
        tmp.erase(key);

        double found = findComplementTwo(val, tmp);
        if (found)
            ans = found * key;
    }
    
    return ans;
}
