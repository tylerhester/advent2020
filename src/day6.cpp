#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream file;
    // file.open("testing6.txt");
    file.open("customsQuestions.txt");

    unordered_map<char, int> questionsAsked;

    int totalAsked = 0;
    string line;
    while(getline(file, line)) {
        if(!line.length()) {
            // Found next batch of questions
            cout << questionsAsked.size() << " + ";
            totalAsked += questionsAsked.size();
            questionsAsked.clear();
        } else {
            // Still on current batch of questions
            // Loop through the current line
            for(auto c : line) {
                if(questionsAsked[c] == 0) {
                    questionsAsked.insert(make_pair(c, 1));
                }
            }
        }
    }

    cout << questionsAsked.size();
    totalAsked += questionsAsked.size();
    questionsAsked.clear();

    cout << " = " << totalAsked << endl;
    
    file.close();
    return 0;
}
